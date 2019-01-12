#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
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

    fd_set rfds;
    fd_set wfds;
    struct timeval tv;
    int retval;
    char buff[1024] = {0};

    map<int, string> clisock;

    while(1)
    {
        int maxfd = sersock;

        FD_ZERO(&rfds);
        FD_ZERO(&wfds);

        FD_SET(sersock, &rfds);
        for( auto pairs : clisock)
        {
            int c = pairs.first;
            string s = pairs.second;
            FD_SET(c, &rfds);
            if(!s.empty())
            {
                cout<<"s info: "<<s<<endl;
                FD_SET(c, &wfds);
            }
            cout<<"set fd: "<<c<<endl;
            maxfd = c>maxfd ? c : maxfd;
        }

        tv.tv_sec = 5;
        retval = select(maxfd+1, &rfds, &wfds, NULL, &tv);
        if(retval < -1)
        {
            cout<<"select error "<<errno<<endl;
            return 0;
        }
        else
        {
            if(FD_ISSET(sersock, &rfds))
            {
                struct sockaddr_in clientaddr;
                socklen_t length = sizeof(clientaddr);
                int c = accept(sersock, (struct sockaddr*)&clientaddr, &length);
                clisock[c] = string("");
                cout<<"new conn "<<c<<endl;
            }
            for( auto &pairs : clisock)
            {
                int c = pairs.first;
                string &s = pairs.second;
                if(FD_ISSET(c, &rfds))
                {
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
                        FD_CLR(c, &wfds);
                        FD_CLR(c, &rfds);
                        cout<<"recv close conn "<<c<<endl;
                    }
                }
                if(FD_ISSET(c, &wfds))
                {
                    if(send(c, s.c_str(), s.size(), 0) > 0)
                    {
                        cout<<"send succ: "<<s<<endl;
                    }
                    else
                    {
                        clisock.erase(c);
                        cout<<"send close conn "<<c<<endl;
                    }
                    s.clear();
                }
            }
        }
    }   

    return 0;
}
