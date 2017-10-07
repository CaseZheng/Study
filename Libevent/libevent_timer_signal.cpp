#include <iostream>
#include <cstring>
#include <sys/signal.h>
#include <event2/event.h>
#include <event2/util.h>

using namespace std;

struct timeval lasttime;

static void timeout_cb(evutil_socket_t fd, short events, void *arg)
{
    struct timeval newtime, difference;
    struct event *timeout = (struct event*)arg;
    double elapsed;
    evutil_gettimeofday(&newtime, NULL);
    evutil_timersub(&newtime, &lasttime, &difference);
    elapsed = difference.tv_sec + (difference.tv_usec / 1.0e6);
    cout<<"timeout_cb called at "<<newtime.tv_sec<<": "<<elapsed<<"second elapsed"<<endl;
    lasttime = newtime;
}

static void signal_cb(evutil_socket_t fd, short events, void *arg)
{
    struct event_base *base = (struct event_base *)arg;
    struct timeval delay = {1, 0};

    cout<<"1 s after exit"<<endl;

    event_base_loopexit(base, &delay);
}

int main()
{
    struct event_base *base = event_base_new();
    if(NULL == base)
    {
        cout<<"event_base_new error"<<endl;
        cout<<strerror(errno)<<endl;
        return 0;
    }

    struct event *signalevent = evsignal_new(base, SIGINT, signal_cb, (void*)base);
    event_add(signalevent, NULL);

    struct event *timeout_event = evtimer_new(base, timeout_cb, NULL);
    //flags设置为EV_PERSIST表示该事件一直有效
    int flags = EV_PERSIST;
    //flags设置为0，该事件触发一次就会被删除，需要再次添加
    //int flags = 0;
    event_assign(timeout_event, base, -1, flags, timeout_cb, (void*) timeout_event);

    struct timeval tv;
    evutil_timerclear(&tv);
    tv.tv_sec = 2;
    event_add(timeout_event, &tv);

    evutil_gettimeofday(&lasttime, NULL);

    event_base_dispatch(base);
    event_free(signalevent);
    event_free(timeout_event);
    event_base_free(base);

    return 0;
}
