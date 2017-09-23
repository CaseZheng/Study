#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <string.h>
#include <string>
#include <unistd.h>


using namespace std;

int main()
{
    int clisock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(9999);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(clisock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        cout<<"connect error "<<errno<<endl;
        return 0;
    }
    cout<<"connect succ "<<endl;

    fd_set rfds;
    fd_set wfds;
    struct timeval tv;
    tv.tv_sec = 5;
    int retval;
    char buff[1024] = {0};

    string input;           //命令行输入
    string serinput;        //服务器返回

    while(1)
    {
        FD_ZERO(&rfds);
        FD_ZERO(&wfds);

        FD_SET(0, &rfds);
        FD_SET(1, &wfds);
        FD_SET(clisock, &rfds);
        FD_SET(clisock, &wfds);

        retval = select(clisock+1, &rfds, &wfds, NULL, &tv);
        if(retval == -1)
        {
            cout<<"select error "<<errno<<endl;
        }
        else
        {
            if(FD_ISSET(0, &rfds))
            {
                cout<<"可读"<<endl;
                cin>>input;
            }
            if(FD_ISSET(1, &wfds) && !serinput.empty())
            {
                cout<<"server return: "<<serinput<<endl;
                serinput.clear();
            }
            if(FD_ISSET(clisock, &rfds))
            {
                char buffer[1024] = {0};
                if(recv(clisock, buffer, sizeof(buffer), 0) < 0)
                {
                    close(clisock);
                    cout<<"close "<<clisock<<endl;
                    return 0;
                }
                serinput = string(buffer);
            }
            if(FD_ISSET(clisock, &wfds) && !input.empty())
            {
                if(send(clisock, input.c_str(), input.size(), 0) > 0)
                {
                    cout<<"send "<<input<<endl;
                }
                else
                {
                    close(clisock);
                    cout<<"close "<<clisock<<endl;
                }
                input.clear();
            }
        }
    }   

    return 0;
}
