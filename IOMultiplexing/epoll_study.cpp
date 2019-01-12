#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <string.h>
#include <string>
#include <map>
#include <unistd.h>


using namespace std;

int main()
{
    int sersock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(9999);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int on = 1;  
    setsockopt(sersock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)); 

    if(bind(sersock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        cout<<"bind error "<<errno<<endl;
        return 0;
    }

    if(listen(sersock, 5) == -1)
    {
        cout<<"listen error "<<errno<<endl;
        return 0;
    }

    int retval;
    int epollfd = epoll_create(1024);
    if(epollfd < 0)
    {
        cout<<"epoll_create error"<<endl;
        return 0;
    }
    struct epoll_event tmpfds;
    tmpfds.events = EPOLLRDNORM;
    tmpfds.data.fd = sersock;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, sersock, &tmpfds);

    char buff[1024] = {0};
    map<int, string> clisock;

    for(;;)
    {
        struct epoll_event fds[1024];
        retval = epoll_wait(epollfd, fds, 1024, -1);
        if(retval < -1)
        {
            cout<<"epoll_wait error "<<errno<<endl;
            return 0;
        }
        else
        {
            for(int i=0; i<retval; ++i)
            {
                if(fds[i].data.fd == sersock && (fds[i].events & EPOLLRDNORM) == EPOLLRDNORM)
                {
                    struct sockaddr_in clientaddr;
                    socklen_t length = sizeof(clientaddr);
                    int c = accept(sersock, (struct sockaddr*)&clientaddr, &length);
                    clisock[c] = string("");
                    tmpfds.data.fd = c;
                    tmpfds.events = EPOLLRDNORM;
                    epoll_ctl(epollfd, EPOLL_CTL_ADD, c, &tmpfds);
                    cout<<"new conn "<<c<<endl;
                    continue;
                }
                int c = fds[i].data.fd;
                auto &s = clisock[c];
                if(fds[i].data.fd != sersock &&  (fds[i].events & EPOLLRDNORM) == EPOLLRDNORM)
                {

                    tmpfds.data.fd = c;
                    tmpfds.events = EPOLLWRNORM | EPOLLRDNORM;
                    epoll_ctl(epollfd, EPOLL_CTL_MOD, c, &tmpfds);
                    char buffer[1024] = {0};
                    if(recv(c, buffer, sizeof(buffer), 0) > 0)
                    {
                        clisock[c] = string(buffer);
                        cout<<"recv: "<<clisock[c]<<endl;
                    }
                    else
                    {
                        clisock.erase(c);
                        close(c);
                        epoll_ctl(epollfd, EPOLL_CTL_DEL, c, NULL);
                        cout<<"recv close conn "<<c<<endl;
                    }
                }
                if((fds[i].events & EPOLLWRNORM) == EPOLLWRNORM)
                {
                    tmpfds.data.fd = c;
                    tmpfds.events = EPOLLRDNORM;
                    epoll_ctl(epollfd, EPOLL_CTL_MOD, c, &tmpfds);
                    if(send(c, s.c_str(), s.size(), 0) > 0)
                    {
                        cout<<"send succ: "<<s<<endl;
                    }
                    else
                    {
                        clisock.erase(c);
                        close(c);
                        epoll_ctl(epollfd, EPOLL_CTL_DEL, c, NULL);
                        cout<<"send close conn "<<c<<endl;
                    }
                    s.clear();
                }
            }
        }
    }   

    return 0;
}
