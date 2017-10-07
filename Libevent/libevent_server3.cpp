#include <iostream>
#include <cstring>
#include <unistd.h>

#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/listener.h>
#include <event2/util.h>

using namespace std;

void accept_cb(evconnlistener *listener, evutil_socket_t fd, \
        struct sockaddr *sock, int socklen, void *arg);
void socket_read_cb(struct bufferevent *bev, void *arg);
void event_cb(struct bufferevent *bev, short event, void *arg);

int main()
{
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(9999);

    event_base *base = event_base_new();

    evconnlistener * listener = evconnlistener_new_bind(base, accept_cb, \
            base, LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE, \
            10, (struct sockaddr*)&sin, \
            sizeof(struct sockaddr_in));

    event_base_dispatch(base);

    evconnlistener_free(listener);
    event_base_free(base);

    return 0;
}

void accept_cb(evconnlistener *listener, evutil_socket_t fd, \
        struct sockaddr *sock, int socklen, void *arg)
{
    cout<<"accept a client fd: "<<fd<<endl;

    event_base *base = (event_base*)arg;

    bufferevent *bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
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
