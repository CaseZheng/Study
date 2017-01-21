/// File: C_Server.cpp
/// Synopsis: 
/// Author: CaseZheng, 764307915@qq.com
/// Version: 
/// Date: 2017-01-21

#include "C_Public.h"

class MainServer;

class Link
{
    public:
        Link(int socketid):
            m_iSocketId(socketid),
            m_iReceiveDataSize(0),
            m_iSendDataSize(0)
        {
            //
        }
        ~Link()
        {
            //
        }
        int GetSocketId() { return m_iSocketId; }
        int Send(void *buf, int size);
        int RealSend();
        int GetSendDataSize() { return m_iSendDataSize; }
        int GetCanSendDataSize() { return BUFSIZE-GetSendDataSize(); }
    private:
        Link(const Link &link);
        Link &operator=(const Link &link);

        bool SetWriteFlag();
        enum
        {
            BUFSIZE = 4*1024,
        };
        int m_iSocketId;
        int m_iReceiveDataSize;
        char m_cReceiveBuf[BUFSIZE];
        int m_iSendDataSize;
        char m_cSendBuf[BUFSIZE];
};

class EventListen
{
    public:
        bool SetFdWriteFlag(int fd)
        {
            int index = GetFdIndex(fd);
            if(index<0 || index>=MAXFDNUM)
            {
                return false;
            }
            m_gFds[index].fd = fd;
            m_gFds[index].events |= POLLIN|POLLERR;
            return true;
        }
        bool SetFdReadFlag(int fd)
        {
            int index = GetFdIndex(fd);
            if(index<0 || index>=MAXFDNUM)
            {
                return false;
            }
            m_gFds[index].fd = fd;
            m_gFds[index].events |= POLLOUT|POLLERR;
            return true;
        }
        bool ClearFdWriteFlag(int fd)
        {
            int index = GetFdIndex(fd);
            if(index<0 || index>=MAXFDNUM)
            {
                return false;
            }
            m_gFds[index].fd = fd;
            m_gFds[index].events &= (~POLLOUT);
            return true;
        }
        static void Run(map<int, int> &Event);

    private:
        enum
        {
            MAXFDNUM = 5000,
            MAXTIME = 3000,
        };
        int GetFdIndex(int fd)
        {
            int index = fd%MAXFDNUM;
            for(int i=0; ; index+=i*2)
            {
                if(index >= MAXFDNUM)
                {
                    index = index%2 + 2;
                }
                if(i!=0 && index==fd%MAXFDNUM)
                {
                    return -1;
                }
                if(EventListen::m_gFds[index].fd == 0 ||
                        EventListen::m_gFds[index].fd == fd)
                {
                    return index;
                }
            }
            return index;
        }
        static struct pollfd m_gFds[MAXFDNUM];
};
struct pollfd EventListen::m_gFds[MAXFDNUM] = {0};

class MainServer
{
    public:
        static bool SetLinkWriteFlag(int socket)
        {
            return m_gEventListen.SetFdWriteFlag(socket);
        }
        static bool SetLinkReadFlag(int socket)
        {
            return m_gEventListen.SetFdReadFlag(socket);
        }
        static bool SetSocketLinkMap(int socket, Link *link) 
        {
            MainServer::GetAllSocketLinkMap()[socket] = link;
            return true;
        }
        static void SetListenFd(int listenfd)
        {
            m_gListenFd = listenfd;
        }
        static int GetListenfd()
        {
            return m_gListenFd;
        }
        static void Run();
    private:
        MainServer();
        ~MainServer();
        MainServer(const MainServer &);
        MainServer &operator=(const MainServer &);

        static map<int, Link*> &GetAllSocketLinkMap()
        {
            return MainServer::m_gAllSocketLinkMap;
        }
        
        static int m_gListenFd;

        static EventListen m_gEventListen;
        static map<int, Link*> m_gAllSocketLinkMap;
};

int MainServer::m_gListenFd = 0;
EventListen MainServer::m_gEventListen = EventListen();
map<int, Link*> MainServer::m_gAllSocketLinkMap = map<int, Link*>();

bool Link::SetWriteFlag()
{
    return MainServer::SetLinkWriteFlag(m_iSocketId);
}

int Link::Send(void *buf, int size)
{
    if(NULL==buf || size<=0)
    {
        error_msg("send msg fail, para error");
        return -1;
    }
    if(GetCanSendDataSize() <= size)
    {
        error_msg("send msg fail, sendbuf not enough");
        return -1;
    }
    memcpy(m_cSendBuf+m_iSendDataSize, buf, size);
    m_iSendDataSize += size;
    MainServer::SetLinkWriteFlag(GetSocketId());
    return 0;
}

int Link::RealSend()
{
    int n = send(GetSocketId(), m_cSendBuf, m_iSendDataSize, 0);
    if(n < 0)
    {
        error_msg("send data error");
        return -1;
    }
    char tmp[BUFSIZE] = {0};
    memcpy(tmp, m_cSendBuf+n, m_iSendDataSize-n);
    memcpy(m_cSendBuf, tmp, m_iSendDataSize-n);
    m_iSendDataSize -= n;
    if(m_iSendDataSize > 0)
    {
        SetWriteFlag();
    }
    return n;
}

void EventListen::Run(map<int, int> &Event)
{
    if(poll(m_gFds, MAXFDNUM, MAXTIME) <= 0)
    {

    }
}

void MainServer::Run()
{
    SetLinkReadFlag(GetListenfd());
    map<int, int> Event;
    EventListen::Run(Event);   
}

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
    error_msg("server_socket init success");

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(10000);

    if(bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
    {
        error_msg("bind error");
    }
    error_msg("bind success");

    if(listen(server_socket, 5) == -1)
    {
        error_msg("listen error");
    }
    error_msg("listen success");

    MainServer::SetListenFd(server_socket);

    MainServer::Run();

    clnt_addr_size = sizeof(client_addr);
    client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &clnt_addr_size);
    if(-1 == client_socket)
    {
        error_msg("accept error");
    }

    const char* msg = "hello lua";
    write(client_socket, msg, strlen(msg)+1);
    close(client_socket);
    close(server_socket);
    return 0;
}
