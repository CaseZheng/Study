#include <iostream>
#include <cstring>

#include <event2/event.h>
#include <event2/dns.h>

using namespace std;


void callback(int errcode, struct evutil_addrinfo *addr, void *ptr)
{
    if (errcode)
    {
        cout<<"error :"<<evutil_gai_strerror(errcode)<<endl;
    }
    else
    {
        struct evutil_addrinfo *ai;
        if (addr->ai_canonname)
        {
            cout<<"cannoname :"<<addr->ai_canonname<<endl;
        }

        //addr是一个链表,遍历链表
        for( ai = addr ; ai != NULL ; ai = ai->ai_next)
        {
            char buf[128];
            const char *s = NULL;
            if ( ai->ai_family == AF_INET)
            {
                struct sockaddr_in *sin = (struct sockaddr_in *)ai->ai_addr;
                s = evutil_inet_ntop(AF_INET, &sin->sin_addr, buf, 128);
            } 
            else if ( ai->ai_family == AF_INET6)
            {
                struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)ai->ai_addr;
                s = evutil_inet_ntop(AF_INET6, &sin6->sin6_addr, buf, 128);
            }
            if(s)
            {
                cout<<"  ->"<<s<<endl;
            }
        }
        evutil_freeaddrinfo(addr);
    }
}

int main()
{
    struct event_base *base = event_base_new();
    struct evdns_base *dnsbase = evdns_base_new(base, 1);
    struct evutil_addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC ; //不指定.
    hints.ai_flags = EVUTIL_AI_CANONNAME; //返回规范名.
    hints.ai_socktype = SOCK_STREAM; //只需要SOCK_STREAM套接字类型
    hints.ai_protocol = IPPROTO_TCP; //只需要TCP协议的.
    const char* nodename = "github.com";
    struct evdns_getaddrinfo_request *req;
    req = evdns_getaddrinfo(dnsbase , nodename , NULL , &hints , callback , NULL);

    event_base_dispatch(base);
    if ( req != NULL)
    {
        free( req );
    }

    evdns_base_free(dnsbase, 0);
    event_base_free(base);

    return 0;
}
