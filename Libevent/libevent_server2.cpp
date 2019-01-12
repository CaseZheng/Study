#include <iostream>
#include <cstring>
#include <unistd.h>

#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/listener.h>
#include <event2/util.h>

using namespace std;

void accept_cb(int fd, short events, void *arg);
void socket_read_cb(struct bufferevent *bev, void *arg);
void event_cb(struct bufferevent *bev, short event, void *arg);
int tcp_server_init(int port, int listen_num);

int main()
{
    int listener = tcp_server_init(9999, 5);
    if(listener == -1)
    {
        cout<<"tcp_server_init error"<<endl;
        return 0;
    }

    struct event_base * base = event_base_new();
    if(NULL == base)
    {
        cout<<"event_base_new error"<<endl;
        return 0;
    }

    struct event * ev_listen = event_new(base, listener, EV_READ|EV_PERSIST, accept_cb, base);
    if(NULL == ev_listen)
    {
        cout<<"event_new error"<<endl;
        return 0;
    }
    event_add(ev_listen, NULL);

    event_base_dispatch(base);

    event_free(ev_listen);
    event_base_free(base);
    return 0;
}

void accept_cb(int fd, short evnets, void *arg)
{
    struct sockaddr_in client;
    socklen_t len = sizeof(client);

    evutil_socket_t sockfd = ::accept(fd, (struct sockaddr*)&client, &len);
    if(sockfd < 0)
    {
        cout<<"accept error"<<endl;
        return;
    }
    evutil_make_socket_nonblocking(sockfd);

    cout<<"accpet a conn fd: "<<sockfd<<endl;
    struct event_base *base = (struct event_base*)arg;

    bufferevent *bev = bufferevent_socket_new(base, sockfd, BEV_OPT_CLOSE_ON_FREE);
    if(NULL == bev)
    {
        cout<<"bufferevent_socket_new error"<<endl;
        close(fd);
        return;
    }
    bufferevent_setcb(bev, socket_read_cb, NULL, event_cb, arg);
    bufferevent_enable(bev, EV_READ | EV_PERSIST);
}

void socket_read_cb(bufferevent *bev, void *arg)
{
    char buff[4096] = {0};
    size_t len = bufferevent_read(bev, buff, sizeof(buff));
    if(len <= 0)
    {
        cout<<"read error len: "<<len<<endl;
        return;
    }
    buff[len] = '\0';
    cout<<"read msg : "<<buff<<endl;

    bufferevent_write(bev, buff, strlen(buff));
}

void event_cb(struct bufferevent *bev, short event, void *arg)
{
    if(event & BEV_EVENT_EOF)
    {
        cout<<"conn close"<<endl;
    }
    else if(event &BEV_EVENT_ERROR)
    {
        cout<<"conn error"<<endl;
    }
    else
    {
        cout<<"event :"<<event<<endl;
    }

    bufferevent_free(bev);
}

int tcp_server_init(int port, int listen_num)
{
    evutil_socket_t listener;
    listener = ::socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0)
    {
        cout<<"create socket error"<<endl;
        return -1;
    }

    evutil_make_listen_socket_reuseable(listener);

    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = 0;
    sin.sin_port = htons(port);
    if(::bind(listener, (struct sockaddr*)&sin, sizeof(sin)) < 0)
    {
        cout<<"bind error"<<endl;
        return -1;
    }
    if(::listen(listener, listen_num) < 0)
    {
        cout<<"listen error"<<endl;
        return -1;
    }

    evutil_make_socket_nonblocking(listener);

    return listener;
}
