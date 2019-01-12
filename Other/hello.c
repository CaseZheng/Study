#define ONE 1
#define TWO 1

#if 0
int flag = ONE;
#else
int flag = TWO;
#endif
int z;

int getFlag()
{
    return flag;
}

//主函数
int main()
{
    int x = getFlag();
    static int y;
    static int w = 3;;
    x = flag;
    return 0;
}
