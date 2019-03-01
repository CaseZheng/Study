#include <iostream>
#include <string>
#include <unistd.h>
#include <pthread.h>
#include <boost/thread/thread.hpp>
#include <boost/chrono.hpp>
#include <boost/ref.hpp>

using namespace std;

void Print1(int *pCount)
{
    for(;(*pCount)<10;++(*pCount))
    {
        cout << "PID:" << getpid() << " TID:" << pthread_self() << "  " << *pCount << endl;
        boost::this_thread::sleep_for(boost::chrono::seconds(1));
    }
}

void Print2(int &count)
{
    for(;count<10;++count)
    {
        cout << "PID:" << getpid() << " TID:" << pthread_self() << "  " << count << endl;
        boost::this_thread::sleep_for(boost::chrono::seconds(1));
    }
}

int main()
{
    int count = 1;
    boost::thread t1(Print1, &count);
    boost::thread t2(Print2, boost::ref(count));
    cout << "t1 id:" << t1.get_id() << endl;
    cout << "t2 id:" << t2.get_id() << endl;
    t1.join();
    t2.join();
    return 0;
}

#if 0
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
#endif
