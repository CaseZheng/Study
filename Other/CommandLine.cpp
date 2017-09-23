#include <unistd.h>
#include <iostream>
#include <getopt.h>
#include <gflags/gflags.h>

using namespace std;

DEFINE_bool(daemon, true, "run daemon mode");
DEFINE_int32(port, 9000, "program listen port");
DEFINE_string(confpath, "./config.ini", "program config path");
DEFINE_double(dou, 0, "double");

// 定义对 FLAGS_port 的检查函数
static bool ValidatePort(const char* name, int32_t value) {
    if (value > 0 && value < 32768) {
        return true;
    }
    printf("Invalid value for --%s: %d\n", name, (int)value);
    return false;
}

// 使用全局 static 变量来注册函数，static 变量会在 main 函数开始时就调用,确保参数检查在main函数进入时已经注册。  
static const bool port_dummy = gflags::RegisterFlagValidator(&FLAGS_port, &ValidatePort);

int main(int argc, char *argv[])
{
    //gflags::RegisterFlagValidator(&FLAGS_port, &ValidatePort);
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    cout<<"daemon: "<<FLAGS_daemon<<endl;
    cout<<"port: "<<FLAGS_port<<endl;
    cout<<"configpath: "<<FLAGS_confpath<<endl;
    cout<<"dou: "<<FLAGS_dou<<endl;

    FLAGS_dou = 9999.8;
    cout<<"after dou: "<<FLAGS_dou<<endl;

    // 使用 SetCommandLineOption 函数对参数进行设置才会调用检查函数
    gflags::SetCommandLineOption("port", "-2");
    cout<<"after port: "<<FLAGS_port<<endl;
    FLAGS_port = -2;
    cout<<"after2 port: "<<FLAGS_port<<endl;

    return 0;
}

#if 0
//getopt_long示例
int main(int argc, char *argv[])
{

    for(auto i=0; i<argc; ++i)
    {
        cout<<"argv "<<i<<" "<<argv[i]<<endl;
    }

    int ch;
    cout<<"optind:"<<optind<<" opterr:"<<opterr<<endl;
    int flag;
    const struct option long_options[] = {            
            {  "append",    1,   NULL,   'a' },     
            {  "help",      0,   NULL,   'h' },     
            {  "verbose",   0,   NULL,   'v'  },      
            {  "output",    1,   &flag,  'o'   },      
            {  NULL,        0,   NULL,   0  }     
        };
    int longindex = 0;
    while((ch = getopt_long(argc, argv, "a:hvb:cde::g", long_options, &longindex)) != -1)
    {
        cout<<"optind:"<<optind<<endl;
        cout<<"ch:"<<ch<<endl;
        switch(ch)
        {
            case 0:
                cout<<"long option "<<longindex<<" "<<long_options[longindex].name;
                if(NULL != optarg)
                {
                    cout<<" arg "<<optarg;
                }
                cout<<endl;
                break;
            case 'a':
            case 'h':
            case 'v':
                cout<<"ch "<<(char)ch<<endl;
                if(NULL != optarg)
                {
                    cout<<"arg "<<optarg;
                }
                cout<<endl;
                break;
            case 'b':
                cout<<"option b "<<endl;
                cout<<"optarg is NULL :"<<(NULL==optarg)<<endl;
                break;
            case 'c':
                cout<<"option c "<<endl;
                break;
            case 'd':
                cout<<"option d "<<endl;
                break;
            case 'e':
                cout<<"option e "<<optarg<<endl;
                break;
            case '?':
                cout<<"option ? "<<endl;
                if(NULL != optarg)
                {
                    cout<<"unkown option "<<optarg<<endl;
                }
                cout<<"unkown longindex "<<longindex<<endl;
                break;
            default:
                cout<<"error option"<<endl;
        }
    }

    for(auto i=0; i<argc; ++i)
    {
        cout<<"after argv "<<i<<" "<<argv[i]<<endl;
    }
    return 0;
}
#endif

#if 0
//getopt 示例
int main(int argc, char *argv[])
{

    for(auto i=0; i<argc; ++i)
    {
        cout<<"argv "<<i<<" "<<argv[i]<<endl;
    }

    int ch;
    cout<<"optind:"<<optind<<" opterr:"<<opterr<<endl;
    while((ch = getopt(argc, argv, "a:bcde::g")) != -1)
    {
        cout<<"optind:"<<optind<<endl;
        switch(ch)
        {
            case 'a':
                cout<<"option a "<<optarg<<endl;
                break;
            case 'b':
                cout<<"option b "<<endl;
                cout<<"optarg is NULL :"<<(NULL==optarg)<<endl;
                break;
            case 'c':
                cout<<"option c "<<endl;
                break;
            case 'd':
                cout<<"option d "<<endl;
                break;
            case 'e':
                cout<<"option e "<<optarg<<endl;
                break;
            case '?':
                cout<<"unkown option "<<optarg<<endl;
                break;
            default:
                cout<<"error option"<<endl;
        }
    }

    for(auto i=0; i<argc; ++i)
    {
        cout<<"after argv "<<i<<" "<<argv[i]<<endl;
    }
    return 0;
}
#endif
