#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

#if 1
int main()
{
    cout << "start fork" << " PID:" << getpid() << endl;
    for(int i=0; i<3; ++i)
    {
        pid_t iPid = fork();
        if(iPid < 0)
        {
            cout << "fork error" << " PID:" << getpid() << endl;
        }
        else if (iPid == 0)
        {
            cout << "child process" << " PID:" << getpid() << " PPID:" << getppid() << endl;
        }
        else
        {
            cout << "parent process" << " PID:" << getpid() << endl;
        }
    }
    sleep(300);

    return 0;
}
#endif

#if 0
int main()
{
    cout << "start fork" << " PID:" << getpid() << endl;
    pid_t iPid = fork();
    if(iPid < 0)
    {
        cout << "fork error" << " PID:" << getpid() << endl;
    }
    else if (iPid == 0)
    {
        cout << "child process" << " PID:" << getpid() << " PPID:" << getppid() << endl;
    }
    else
    {
        cout << "parent process" << " PID:" << getpid() << endl;
    }

    sleep(300);

    return 0;
}
#endif
