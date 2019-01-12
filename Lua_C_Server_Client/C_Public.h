/// File: C_Public.h
/// Synopsis: 
/// Author: CaseZheng, 764307915@qq.com
/// Version: 
/// Date: 2017-01-21

#ifndef __C_PUBLIC_H__
#define __C_PUBLIC_H__

#include <iostream>
#include <map>
#include <vector>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#include <time.h>
#include <errno.h>
#include <poll.h>

using namespace std;

void error_msg(const char * s)
{
    cout<<s<<endl;
}

#endif
