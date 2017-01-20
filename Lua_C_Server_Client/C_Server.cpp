#include <iostream>
#include <sys/socket.h>

using namespace std;

int main (int argc, char* argv[])
{
    int server_socket;
    int client_socket;

    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    socklen_t clnt_addr_size;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == server_socket)
    {
        error_msg("server_socket init error");
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = hosts(10000);

    if(bind(server_sock, (struct socketaddr*)&server_addr, sizeof(server_addr)) == -1)
    {
        error_msg("bind error");
    }

    if(listen(server_socket, 5) == -1)
    {
        error_msg("listen error");
    }

    clnt_addr_size = sizeof(client_addr);
    client_socket = accept(serv_sock, (struct sockaddr*)&client_addr, &clnt_addr_size);
    if(-1 == client_socket)
    {
        error_msg("accept error");
    }

    const char* msg = "hello lua";
    write(client_socket, "hello lua", strlen(msg)+1);
    close(client_socket);
    close(server_socket);
    return 0;
}
