/// File: C_Client.cpp
/// Synopsis: 
/// Author: CaseZheng, 764307915@qq.com
/// Version: 
/// Date: 2017-01-21

#include "C_Public.h"

int main(int argc, char **argv)
{
    int sock;
    struct sockaddr_in serv_addr;
    int str_len;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == sock)
    {
        error_msg("socket init error");
    }
    error_msg("socket init success");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(10000);

    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
    {
        error_msg("connect error");
    }
    error_msg("connect success");


    const char* msg = "hello lua";
    write(sock, msg, strlen(msg)+1);

    char massage[1024] = {0};
    str_len = read(sock, massage, sizeof(massage)-1);
    if(-1==str_len)
    {
        error_msg("read error");
    }

    cout<<"massage:"<<massage<<endl;

    close(sock);

    return 0;
}
