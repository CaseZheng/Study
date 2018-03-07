#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <stack>
#include <queue> 

using namespace std;


void PrintVec(vector<int> &vec)
{
    for(auto x : vec)
    {
        cout<<x<<" ";
    }
    if(vec.size()>0)
    {
        cout<<endl;
    }
}


void InsertSort(vector<int> &vec)   //插入排序
{
    if(vec.size() <= 1)
    {
        return;
    }
    for(int i=1; i<vec.size(); ++i)
    {
        int tmpIndex = i;
        for(int j=0; j<i; ++j)
        {
            if(vec[j] > vec[i])
            {
                tmpIndex = j;
                break;
            }
        }
        int tmpValue = vec[i];
        for(int j=i; j>tmpIndex; --j)
        {
            vec[j] = vec[j-1];
        }
        vec[tmpIndex] = tmpValue;
        //PrintVec(vec);
    }
}

void Swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

void BubbleSinkSort(vector<int> &vec)   //冒泡排序（下沉）
{
    if(vec.size() <= 1)
    {
        return;
    }

    for(int i=vec.size()-1; i>0; --i)
    {
        bool flag = false;
        int end = vec.size()-1-i;
        for(int j=vec.size()-1; j>end; --j)
        {
            if(vec[j] < vec[j-1])
            {
                Swap(vec[j], vec[j-1]);
                flag = true;
            }
        }
        if(!flag)
        {
            break;
        }
        //PrintVec(vec);
    }
}

void BubbleFloatSort(vector<int> &vec)   //冒泡排序（上浮）
{
    if(vec.size() <= 1)
    {
        return;
    }

    for(int i=0; i<vec.size(); ++i)
    {
        bool flag = false;
        int end = vec.size()-1-i;
        for(int j=0; j<end; ++j)
        {
            if(vec[j] > vec[j+1])
            {
                Swap(vec[j], vec[j+1]);
                flag = true;
            }
        }
        if(!flag)
        {
            break;
        }
        //PrintVec(vec);
    }
}

void SelectionSort(vector<int> &vec)        //选择排序
{
    if(vec.size() <= 1)
    {
        return;
    }
    for(int i=0; i<vec.size(); ++i)
    {
        int minValue = vec[i];
        int minIndex = i;
        for(int j=i+1; j<vec.size(); ++j)
        {
            if(vec[j] < minValue)
            {
                minValue = vec[j];
                minIndex = j;
            }
        }
        Swap(vec[i], vec[minIndex]);
    }
}

int Partition(vector<int> &vec, int l, int r)
{
    if(l>r)
    {
        return l;
    }
    int position;
    int index = r;
    int tmpValue = vec[index];
    while(l<r)
    {
        while(l<r && vec[l]<tmpValue) ++l;   //从左边向右找一个大于tmpValue的下标l
        while(l<r && vec[r]>=tmpValue) --r;  //从右边向左找一个小于tmpValue的下标r
        if(l<r)
        {
            Swap(vec[l], vec[r]);           //交换两个值
        }
    }
    Swap(vec[l], vec[index]);

    //PrintVec(vec);
    return r;
}

void QuickSort_Recursion(vector<int> &vec, int l, int r)
{
    int position = 0;
    if(l<r)
    {
        position = Partition(vec, l, r);
        QuickSort_Recursion(vec, l, position-1);
        QuickSort_Recursion(vec, position+1, r);
    }
}

void QuickSort_Recursion(vector<int> &vec)    //快速排序（递归）
{
    if(vec.size() <= 1)
    {
        return;
    }
    QuickSort_Recursion(vec, 0, vec.size()-1);
}

void QuickSort(vector<int> &vec)            //快速排序（迭代）
{
    if(vec.size() <= 1)
    {
        return;
    }
    int l = 0;
    int r = vec.size()-1;
    stack<int> st;
    st.push(l);
    st.push(r);
    while(!st.empty())
    {
        r = st.top(); st.pop();
        l = st.top(); st.pop();
        if(l >= r)
        {
            continue;
        }
        int position = Partition(vec, l, r);
        st.push(l); 
        st.push(position-1);

        st.push(position+1);
        st.push(r);
    }
}

void Merge(vector<int> &va, vector<int> &vb, vector<int> &vec)
{
    vec.clear();
    if(va.empty())
    {
        vec = vb;
    }
    else if(vb.empty())
    {
        vec = va;
    }
    else 
    {
        int a = 0;
        int b = 0;
        while(a < va.size() && b < vb.size())
        {
            if(va[a] < vb[b])
            {
                vec.push_back(va[a++]);
            }
            else 
            {
                vec.push_back(vb[b++]);
            }
        }
        if(a < va.size())
        {
            for(; a<va.size(); ++a)
            {
                vec.push_back(va[a]);
            }
        }
        if(b < vb.size())
        {
            for(; b<vb.size(); ++b)
            {
                vec.push_back(vb[b]);
            }
        }
    }
}

void MergeSort_Recursion(vector<int> &vec)  //归并排序（递归）
{
    if(vec.size() <= 1)
    {
        return;
    }
    vector<int> va;
    vector<int> vb;
    int mod = vec.size()/2;
    for(int i=0; i<vec.size(); ++i)
    {
        if(i<mod)
        {
            va.push_back(vec[i]);
        }
        else 
        {
            vb.push_back(vec[i]);
        }
    }
    MergeSort_Recursion(va);
    MergeSort_Recursion(vb);
    Merge(va, vb, vec);
}

void Merge(vector<int> &vec, int x, int y, int z)
{
    vector<int> va;
    vector<int> vb;
    for(int i=x; i<y; ++i)
    {
        va.push_back(vec[i]);
    }
    for(int i=y; i<z; ++i)
    {
        vb.push_back(vec[i]);
    }
    vector<int> vc;
    if(va.empty())
    {
        vc = vb;
    }
    else if(vb.empty())
    {
        vc = va;
    }
    else 
    {
        int a = 0;
        int b = 0;
        while(a < va.size() && b < vb.size())
        {
            if(va[a] < vb[b])
            {
                vc.push_back(va[a++]);
            }
            else 
            {
                vc.push_back(vb[b++]);
            }
        }
        if(a < va.size())
        {
            for(; a<va.size(); ++a)
            {
                vc.push_back(va[a]);
            }
        }
        if(b < vb.size())
        {
            for(; b<vb.size(); ++b)
            {
                vc.push_back(vb[b]);
            }
        }
    }
    for(int i=x; i<z; ++i)
    {
        vec[i] = vc[i-x];
    }
}

int min(int a, int b)
{
    return (a<b ? a : b);
}

void MergeSort(vector<int> &vec)            //归并排序（迭代）
{
    if(vec.size() <= 1)
    {
        return;
    }
    for(int i=1; i<vec.size(); i*=2)
    {
        int offset = i+i;
        for(int j=0; j<vec.size(); j+=offset)
        {
            Merge(vec, j, min(j+i, vec.size()), min(j+offset, vec.size())); 
            //cout<<j<<" "<<min(j+i, vec.size())<<" "<<min(j+offset, vec.size())<<endl;
            //PrintVec(vec);
        }
    }
}

void KeepHead(vector<int> &vec, int len, int i)
{
    int left = 2*i+1;
    int right = 2*i+2;
    int largest = i;
    if(left<len && vec[left]>vec[i])
    {
        largest = left;
    }
    if(right<len && vec[right]>vec[largest])
    {
        largest = right;
    }
    if(largest != i)
    {
        Swap(vec[i], vec[largest]);
        KeepHead(vec, len, largest);
    }
}

void BuildHeap(vector<int> &vec)                //建堆
{
    if(vec.size() < 2)
    {
        return;
    }
    int i = vec.size()/2 -1;
    while(i>=0)
    {
        KeepHead(vec, vec.size(), i);
        --i;
    }
}

void HeapSort(vector<int> &vec)                 //堆排序
{
    BuildHeap(vec);
    int heap_size = vec.size();
    for(int i=vec.size()-1; i>0; --i)
    {
        //PrintVec(vec);
        Swap(vec[0], vec[i]);
        --heap_size;
        KeepHead(vec, heap_size, 0);
    }
}

void CountingSort(vector<int> &vec)             //计数排序
{
    if(vec.size() < 1)
    {
        return;
    }
    int maxValue = vec[0];
    int minValue = vec[0];
    for(auto x : vec)
    {
        maxValue = x>maxValue ? x : maxValue;
        minValue = x<minValue ? x : minValue;
    }
    vector<int> c(maxValue-minValue+1, 0);
    for(auto x : vec)
    {
        ++c[x-minValue];        //统计vec各元素出现的次数
    }
    for(int i=1; i<=maxValue-minValue; ++i)
    {
        c[i] += c[i-1];         //分布值计算
    }
    vector<int> s(vec.size(), 0);
    for(int i=vec.size()-1; i>=0; --i)
    {
        int j = vec[i] - minValue;
        s[c[j]-1] = vec[i];
        --c[j];
    }
    vec = s;
}

void ShellSort(vector<int> &vec)                //希尔排序 
{
    if(vec.size() < 2)
    {
        return;
    }
    int i, j, flag, counter=1, gap=vec.size();
    int temp;
    while(gap > 1)
    {
        gap = gap/2;
        do 
        {
            flag = 0;
            for(int i=0; i<=vec.size()-gap-counter; ++i)
            {
                j=i+gap;
                if(vec[i] > vec[j])
                {
                    Swap(vec[i], vec[j]);
                    flag = 1;
                }
            }
        }
        while(counter < vec.size() && flag == 1);
    }
}

int main()
{
    vector<int> vecTest = {4, 9, 7, 20, 3, 16, 18};
    vector<int> vec;

    //cout<<"插入排序"<<endl         ; vec = vecTest ; PrintVec(vec) ; InsertSort(vec)          ; PrintVec(vec) ;
    //cout<<"冒泡排序（下沉）"<<endl ; vec = vecTest ; PrintVec(vec) ; BubbleSinkSort(vec)      ; PrintVec(vec) ;
    //cout<<"冒泡排序（上浮）"<<endl ; vec = vecTest ; PrintVec(vec) ; BubbleFloatSort(vec)     ; PrintVec(vec) ;
    //cout<<"选择排序"<<endl         ; vec = vecTest ; PrintVec(vec) ; SelectionSort(vec)       ; PrintVec(vec) ;
    //cout<<"快速排序（递归）"<<endl ; vec = vecTest ; PrintVec(vec) ; QuickSort_Recursion(vec) ; PrintVec(vec) ;
    //cout<<"快速排序（迭代）"<<endl ; vec = vecTest ; PrintVec(vec) ; QuickSort(vec)           ; PrintVec(vec) ;
    //cout<<"归并排序（递归）"<<endl ; vec = vecTest ; PrintVec(vec) ; MergeSort_Recursion(vec) ; PrintVec(vec) ;
    //cout<<"归并排序（迭代）"<<endl ; vec = vecTest ; PrintVec(vec) ; MergeSort(vec)           ; PrintVec(vec) ;
    //cout<<"计数排序"<<endl         ; vec = vecTest ; PrintVec(vec) ; CountingSort(vec)        ; PrintVec(vec) ;
    //cout<<"堆排序"<<endl           ; vec = vecTest ; PrintVec(vec) ; HeapSort(vec)            ; PrintVec(vec) ;
    //cout<<"希尔排序"<<endl         ; vec = vecTest ; PrintVec(vec) ; ShellSort(vec)           ; PrintVec(vec) ;

    vecTest = {49, 55, 25, 97, 60, 27, 49, 50} ;

    //cout<<"快速排序（递归）"<<endl ; vec = vecTest ; PrintVec(vec) ; QuickSort_Recursion(vec) ; PrintVec(vec) ;
    //cout<<"快速排序（迭代）"<<endl ; vec = vecTest ; PrintVec(vec) ; QuickSort(vec)           ; PrintVec(vec) ;
    //cout<<"归并排序（递归）"<<endl ; vec = vecTest ; PrintVec(vec) ; MergeSort_Recursion(vec) ; PrintVec(vec) ;
    //cout<<"归并排序（迭代）"<<endl ; vec = vecTest ; PrintVec(vec) ; MergeSort(vec)           ; PrintVec(vec) ;

	return 0;
}
