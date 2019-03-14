#include <iostream>
#include <string>
#include <unistd.h>
#include <pthread.h>
#include "co_routine.h"

using namespace std;

struct SCoInfo
{
    stCoRoutine_t *m_pCo;
    int m_iId;
};

void *Print(void *pArg)
{
    SCoInfo *pCo = (SCoInfo*)pArg;
    for(int i=0; i<10; ++i)
    {
        cout << "PID:" << getpid() << " TID:" << pthread_self() << "  CoId:" << pCo->m_iId << " i:" << i << endl;
        co_resume(pCo->m_pCo);
        co_yield_ct();
    }

    exit(1);
    return NULL;
}

int main()
{
    SCoInfo sCo1{NULL, 1};
    SCoInfo sCo2{NULL, 2};
    co_create(&sCo1.m_pCo, NULL, Print, &sCo2);
    co_create(&sCo2.m_pCo, NULL, Print, &sCo1);

    co_resume(sCo1.m_pCo);
    co_resume(sCo2.m_pCo);

    co_eventloop(co_get_epoll_ct(), NULL, NULL);

    return 0;
}
