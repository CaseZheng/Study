#include <iostream>

#include <event2/event.h>
#include <event2/http.h>
#include <event2/buffer.h>

using namespace std;

void callback(struct evhttp_request *request, void *arg)
{
    const struct evhttp_uri * uri = evhttp_request_get_evhttp_uri(request);
    char url[8192] = {0};
    evhttp_uri_join(const_cast<struct evhttp_uri*>(uri), url, 8192);
    cout<<"accept request url:"<<url<<endl;
    struct evbuffer *evbuf = evbuffer_new();
    if(NULL == evbuf)
    {
        cout<<"error! evbuffer_new"<<endl;
        return;
    }
    evbuffer_add_printf(evbuf, "%s", "hello libevent http");
    evhttp_send_reply(request, HTTP_OK, "OK", evbuf);
    evbuffer_free(evbuf);

}

int main()
{
    struct event_base *base = event_base_new();
    struct evhttp *http = evhttp_new(base);
    evhttp_bind_socket(http, "0.0.0.0", 9999);
    evhttp_set_gencb(http, callback, NULL);

    event_base_dispatch(base);

    event_base_free(base);
    return 0;
}
