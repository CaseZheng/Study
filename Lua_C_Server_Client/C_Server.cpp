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
        int Send(const void *buf, int size);
        int RealSend();
        int RealReceive();
        int GetSendDataSize() { return m_iSendDataSize; }
        int GetCanSendDataSize() { return BUFSIZE-GetSendDataSize(); }
    private:
        Link(const Link &link);
        Link &operator=(const Link &link);

        bool SetWriteFlag();
        bool SetReadFlag();
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
            m_gFds[index].events |= POLLOUT|POLLERR;
            return true;
        }
        bool SetFdReadFlag(int fd)
        {
            int index = GetFdIndex(fd);
            cout<<"set fd:"<<fd<<"read flag index:"<<index<<endl;
            if(index<0 || index>=MAXFDNUM)
            {
                return false;
            }
            m_gFds[index].fd = fd;
            m_gFds[index].events |= POLLIN|POLLERR;
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
        bool DeleteFd(int fd)
        {
            int index = GetFdIndex(fd);
            if(index<0 || index>=MAXFDNUM)
            {
                return false;
            }
            m_gFds[index].fd = 0;
            m_gFds[index].events = 0;
            m_gFds[index].revents = 0;
            return true;
        }
        int Run();
        int GetNextEvent()
        {
            int oldcur = m_gEventCur;
            cout<<"EventCur"<<m_gEventCur<<endl;
            for(int i=m_gEventCur+1; i<MAXFDNUM; ++i)
            {
                if(m_gFds[i].revents != 0)
                {
                    cout<<"i:"<<i<<" event fd"<<m_gFds[i].fd<<endl;
                    return m_gFds[i].fd;
                }
                sleep(1);
                m_gEventCur = i==MAXFDNUM-1 ? 0 : i;
                cout<<"EventCur"<<m_gEventCur<<endl;
                if(i == oldcur)
                {
                    return -1;
                }
            }
            return 0;
        }
        int GetFdEvent(int fd)
        {
            if(fd>=0 && fd<MAXFDNUM)
            {
                return m_gFds[fd].revents;
            }
            return 0;
        }
    private:
        enum
        {
            MAXFDNUM = 50,
            MAXTIME = 5000,
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
        static int m_gEventCur;
        static struct pollfd m_gFds[MAXFDNUM];
};
struct pollfd EventListen::m_gFds[MAXFDNUM] = {0};
int EventListen::m_gEventCur = 0;

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
        static bool ResetLink(int socket)
        {
            GetEventListen().DeleteFd(socket);
            return true;
        }
        static bool DestroyLink(int socket)
        {
            ResetLink(socket);
            close(socket);
            map<int, Link*>::iterator it = GetAllSocketLinkMap().find(socket);
            Link *link = (it->second);
            delete link;
            if(it != GetAllSocketLinkMap().end())
            {
                GetAllSocketLinkMap().erase(it);
            }
            return true;
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
        static EventListen &GetEventListen()
        {
            return m_gEventListen;
        }
        static void Run();
        static Link *GetLinkBySocketfd(int socketfd)
        {
            return m_gAllSocketLinkMap[socketfd];
        }
        static void CreateNewLink();
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
bool Link::SetReadFlag()
{
    return MainServer::SetLinkReadFlag(m_iSocketId);
}
int Link::Send(const void *buf, int size)
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
    else
    {
        MainServer::GetEventListen().ClearFdWriteFlag(GetSocketId());
    }
    return n;
}

int Link::RealReceive()
{
    int n = recv(GetSocketId(), m_cReceiveBuf+m_iReceiveDataSize, BUFSIZE-m_iReceiveDataSize, 0);
    if(n<0)
    {
        return n;
    }
    if(n+m_iReceiveDataSize == BUFSIZE)
    {
        error_msg("receive buf full");
    }
    m_iReceiveDataSize += n;
    cout<<"recv data size:"<<n<<endl;
    sleep(1);

    error_msg(m_cReceiveBuf);
    Send("hello",6);
    return n;
}

int EventListen::Run()
{
    int n = 0;
    error_msg("start poll");
    if((n = poll(m_gFds, MAXFDNUM, MAXTIME)) <= 0)
    {
        //
    }
    cout<<"n:"<<n<<endl;
    return n;
}

void MainServer::CreateNewLink()
{
    int client_socket;
    struct sockaddr_in client_addr;
    int clnt_addr_size = sizeof(client_addr);
    client_socket = accept(GetListenfd(), (struct sockaddr*)&client_addr, &clnt_addr_size);
    if(-1 == client_socket)
    {
        error_msg("accept error");
        return;
    }

    Link *link = new Link(client_socket);
    GetAllSocketLinkMap()[link->GetSocketId()] = link;
    GetEventListen().SetFdReadFlag(link->GetSocketId());
}

void MainServer::Run()
{
    SetLinkReadFlag(GetListenfd());
    error_msg("start run");
    for(;;)
    {
        int n = m_gEventListen.Run();   
        for(int i=0; i<n; ++i)
        {
            int socketfd = GetEventListen().GetNextEvent();
            int revents = GetEventListen().GetFdEvent(socketfd);
            if(-1 == revents)
            {
            }
            if(revents & POLLIN)
            {
                if(socketfd == GetListenfd())
                {
                    error_msg("new link");
                    CreateNewLink();
                }
                else
                {
                    Link *link = GetLinkBySocketfd(socketfd);
                    error_msg("read data");
                    sleep(1);
                    cout<<link<<endl;
                    if(NULL != link)
                    {
                       int n = link->RealReceive();
                       if(n<0)
                       {
                           MainServer::DestroyLink(link->GetSocketId());
                       }
                    } 
                }
            }
            if(revents & POLLOUT)
            {
                Link *link = GetLinkBySocketfd(socketfd);
                error_msg("send data");
                sleep(1);
                if(NULL != link)
                {
                   link->RealSend();
                }
            }
            if(revents & POLLERR)
            {
                error_msg("error data");
                sleep(1);
            }
        }
    }
}

int main (int argc, char* argv[])
{
    int server_socket;

    struct sockaddr_in server_addr;

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

    close(server_socket);
    return 0;
}
