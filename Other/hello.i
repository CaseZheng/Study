# 1 "hello.c"
# 1 "<built-in>"
# 1 "<命令行>"
# 31 "<命令行>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<命令行>" 2
# 1 "hello.c"






int flag = 1;

int z;

int getFlag()
{
    return flag;
}


int main()
{
    int x = getFlag();
    static int y;
    static int w = 3;;
    x = flag;
    return 0;
}
