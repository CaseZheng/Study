#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/poll.h>
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
    struct pollfd fds[1024] = {-1, 0, 0};
    fds[0].fd = sersock;
    fds[0].events = POLLRDNORM;

    char buff[1024] = {0};
    int maxi = 0;

    map<int, string> clisock;

    for(;;)
    {
        retval = poll(fds, maxi+1, -1);
        if(retval < -1)
        {
            cout<<"poll error "<<errno<<endl;
            return 0;
        }
        else
        {
            if(POLLRDNORM == (fds[0].revents & POLLRDNORM))
            {
                struct sockaddr_in clientaddr;
                socklen_t length = sizeof(clientaddr);
                int c = accept(sersock, (struct sockaddr*)&clientaddr, &length);
                clisock[c] = string("");
                fds[++maxi].fd = c;
                fds[maxi].events = POLLRDNORM;
                fds[maxi].revents = 0;
                cout<<"new conn "<<c<<endl;
            }
            for(int i=1; i<1024; ++i)
            {
                if(fds[i].fd < 0)
                {
                    continue;
                }
                int &c = fds[i].fd;
                auto &s = clisock[fds[i].fd];
                if(POLLRDNORM == (fds[i].revents & POLLRDNORM))
                {
                    fds[i].revents &= ~POLLRDNORM;
                    char buffer[1024] = {0};
                    if(recv(c, buffer, sizeof(buffer), 0) > 0)
                    {
                        clisock[c] = string(buffer);
                        cout<<"recv: "<<clisock[c]<<endl;
                        fds[i].events |= POLLWRNORM;
                    }
                    else
                    {
                        clisock.erase(c);
                        close(c);
                        fds[i].fd = -1;
                        fds[i].events = 0;
                        fds[i].revents = 0;
                        cout<<"recv close conn "<<c<<endl;
                    }
                }
                if(POLLWRNORM == (fds[i].revents & POLLWRNORM))
                {
                    fds[i].revents &= ~POLLWRNORM;
                    if(send(c, s.c_str(), s.size(), 0) > 0)
                    {
                        cout<<"send succ: "<<s<<endl;
                    }
                    else
                    {
                        clisock.erase(c);
                        close(c);
                        cout<<"send close conn "<<c<<endl;
                    }
                    fds[i].events &= ~POLLWRNORM;
                    s.clear();
                }
                fds[i].revents = 0;
            }
        }
    }   

    return 0;
}
