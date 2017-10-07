#include <iostream>
#include <cstring>
#include <unistd.h>

#include <event2/event.h>
#include <event2/listener.h>
#include <event2/util.h>

using namespace std;

void accept_cb(int fd, short events, void *arg);
void socket_read_cb(int fd, short events, void *arg);
int tcp_server_init(int port, int listen_num);
void log_cb(int severity, const char *msg);
void exit_cb(int exitcode)
{
    cout<<"exitcode: "<<exitcode<<endl;
    exit(exitcode);
}

void *my_malloc(size_t sz)
{
    cout<<"my_malloc size: "<<sz<<endl;
    void * p = malloc(sz);
    cout<<"ptr: "<<long(p)<<endl;
    return p;
}

void *my_realloc(void *ptr, size_t sz)
{
    cout<<"my_realloc ptr: "<<long(ptr)<<" size: "<<sz<<endl;
    void * p = realloc(ptr, sz);
    cout<<"my_realloc ptr: "<<long(ptr)<<" size: "<<sz<<endl;
    return p;
}

void my_free(void *ptr)
{
    cout<<"my_free ptr: "<<(long)ptr<<endl;
    return free(ptr);
}

int main()
{
    event_set_mem_functions(my_malloc, \
            my_realloc, \
            my_free);

    event_set_log_callback(log_cb);

    event_enable_debug_logging(EVENT_DBG_ALL);

    event_set_fatal_callback(exit_cb);

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
    struct event *ev = event_new(NULL, -1, 0, NULL, NULL);
    event_assign(ev, base, sockfd, EV_READ|EV_PERSIST, socket_read_cb, (void*)ev);
    event_add(ev, NULL);
}

void socket_read_cb(int fd, short events, void *arg)
{
    char buff[4096] = {0};
    struct event *ev = (struct event*)arg;
    int len = read(fd, buff, sizeof(buff)-1);
    if(len <= 0)
    {
        cout<<"read error len: "<<len<<endl;
        event_free(ev);
        close(fd);
        return;
    }
    buff[len] = '\0';
    cout<<"read msg : "<<buff<<endl;

    write(fd, buff, strlen(buff));
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

void log_cb(int severity, const char *msg)
{
    cout<<severity<<" "<<msg<<endl;
}
