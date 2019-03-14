#include <iostream>
#include <math.h>
#include <memory.h>

using namespace std;

int main()
{
    int n = 1000;
    int x = (log(1000)/log(2)) + 1;
    cout << "最小分解个数为: " << x << endl;

    int *arr = new int[x];
    for(int i=0; i<(x-1); ++i)
    {
        arr[i] = pow(2, i);
    }
    arr[x-1] = n-pow(2, x-1)+1;

    cout << "分解后的序列: ";
    for(int i=0; i<x; ++i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;


    //验证下是否正确
    bool *bArr = new bool[n];
    memset(bArr, 0, sizeof(bool)*n);

    for(int i=0; i<n; ++i)
    {
    }

    delete [] bArr;
    delete [] arr;

    return 0;
}
