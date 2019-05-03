#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <signal.h>

void daemon()
{
    //屏蔽控制终端操作信号
    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGHUP,  SIG_IGN);

    signal(SIGCHLD, SIG_IGN);    //忽略子进程结束信号，避免僵死进程产生
    pid_t pid = fork(); //创建子进程
    if(0 != pid)
    {
        std::cout << __LINE__ << "父进程:" << getpid() << "退出" << std::endl;
        std::fflush(stdout);
        exit(0);        //父进程退出,子进程继续运行
    }
    setsid();       //子进程脱离控制终端,登陆会话和进程组,成为无终端的会话组长
    pid = fork();       //创建孙进程
    if(0 != pid)
    {
        std::cout << __LINE__ << "子进程:" << getpid() << "退出" << std::endl;
        std::fflush(stdout);
        exit(0);        //让子进程退出,孙进程继续运行,孙进程不再是会话组长,禁止程序重新打开控制终端
    }
    std::cout << __LINE__ << "孙进程:" << getpid() << "继续运行" << " PPID:" << getppid() << std::endl;
    std::fflush(stdout);
    chdir("/");     //改变工作目录
    umask(0);       //重设文件创建掩码
    for(unsigned i=0; i<3; ++i)
    {
        close(i);       //关闭标准输入,标准输出,标准错误输出
    }
    std::cout << __LINE__ << "关闭标准输入,标准输出,标准错误输出" << std::endl;
    std::fflush(stdout);
    return;
}

int main()
{
    daemon();
    sleep(60);
    return 0;
}
