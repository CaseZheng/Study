#include <iostream>
#include <string>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>

using namespace std;

void *Print(void *pArg)
{
    int *pCount = (int*)pArg;
    for(;*pCount<10;++(*pCount))
    {
        cout << "PID:" << getpid() << " TID:" << pthread_self() << "  " << *pCount << endl;
        sleep(1);
    }
}

int main()
{
    pthread_t t1;
    pthread_t t2;

    int iCount = 0;
    if(pthread_create(&t1, NULL, Print, &iCount) == -1)
    {
        cout << "thread create error" << endl;
        return 1;
    }

    if(pthread_create(&t2, NULL, Print, &iCount) == -1)
    {
        cout << "thread create error" << endl;
        return 1;
    }

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
