#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <stack>
#include <queue> 
using namespace std;


//加权图的邻接矩阵存储
template<class DataType>
class AdjacencyGraphic
{
public:
    AdjacencyGraphic(int Vertice=10, DataType noEdge=0, bool Check=true)
        : v(Vertice), a(v, vector<DataType>(v, noEdge)), e(0), NoEdege(noEdge), check(Check) 
    {
        cout<<__FUNCTION__<<endl;
    }
    ~AdjacencyGraphic()
    {
        cout<<__FUNCTION__<<endl;
    }
    bool exist(int i, int j) const //判断两点间是否有边
    {
        if(i<v && j<v && i>=0 && j>=0)
        {
            return a[i][j]!=NoEdege;
        }
        return false;
    }
    int edges() const              //返回图的边数
    {
        return e;
    }
    int vertices() const           //返回图的顶点数
    {
        return v;
    }
    AdjacencyGraphic<DataType> &add(int i, int j, const DataType &w)   //添加边
    {
        if(i<v && j<v && i>=0 && j>=0 && w!=NoEdege)
        {
            a[i][j] = w;
            if(!check)
            {
                a[j][i] = w;
            }
            ++e;
        }
        return *this;
    }
    AdjacencyGraphic<DataType> &del(int i, int j)   //删除边
    {
        if(i<v && j<v && i>=0 && j>=0 && a[i][j]!=NoEdege)
        {
            a[i][j] = NoEdege;
            if(!check)
            {
                a[j][i] = NoEdege;
            }
            --e;
        }
        return *this;
    }

    int outDegree(int i) const     //计算顶点的出度
    {
        if(i>v-1 || i<0)
        {
            return 0;
        }

        int ret = 0;
        for(auto it : a[i])
        {
            if(it!=NoEdege)
            {
                ++ret;
            }
        }
        return ret;
    }

    int inDegree(int i) const      //计算顶点的入度
    {
        if(i>v-1 || i<0)
        {
            return 0;
        }

        int ret = 0;
        for(auto it : a)
        {
            if(it[i]!=NoEdege)
            {
                ++ret;
            }
        }
        return ret;
    }
    void print() const
    {
        for(auto it=a.begin(); it!=a.end(); ++it)
        {
            for(auto iter=it->begin(); iter!=it->end(); ++iter)
            {
                cout << *iter << " ";
            }
            cout<<endl;
        }
    }
    
    /**
     * Synopsis: dfs_recursion 深度优先遍历 递归法
     */
    void dfs_recursion() const 
    {
        vector<bool> flag(false, v);
        dfs_recursion(flag, 0);
        cout<<endl;
    }

    /**
     * Synopsis: dfs_stack 深度优先比遍历 使用栈
     */
    void dfs_stack()
    {
        stack<int> s;
        s.push(0);

        for(;s.size()!=0;)
        {
            int i = s.top();
            s.pop();
            cout << i << "__";
            for(int j=0; j<v; ++j)
            {
                if(a[i][j] != NoEdege)
                {
                    s.push(j);
                }
            }
        }
        cout << endl;
    }

    /**
     * Synopsis: bfs_queue 广度优先遍历 队列
     */
    void bfs_queue()
    {
        queue<int> q;
        vector<bool> flag(v, false);
        q.push(0);
        for(;q.size()!=0;)
        {
            int i=q.front();
            q.pop();
            flag[i] = true;
            cout << i << "__";
            for(int j=0; j<v; ++j)
            {
                if(a[i][j] != NoEdege && !flag[j])
                {
                    q.push(j);
                }
            }
        }
        cout << endl;
    }


private:
    void dfs_recursion(vector<bool> &flag, int i) const
    {
        cout << i << "__";
        flag[i] = true;
        for(int j=0; j<v; ++j)
        {
            if(a[i][j] != NoEdege && !flag[j])
            {
                //cout << i << "---" << j <<endl;
                dfs_recursion(flag, j);
            }
        }
    }

    DataType NoEdege;
    int v;                          //顶点数
    int e;                          //边数
    vector<vector<DataType> > a;    //二维数组
    bool check;                     //true为有向图 false为无向图
};

template<class DataType>
class LinkedGraph
{
public:
    LinkedGraph(int Vertices=10, bool Check=true) : v(Vertices), check(Check), e(0), h(vector<list<DataType>>(v, list<DataType>()))
    {
        cout<<__FUNCTION__<<endl;
    }
    ~LinkedGraph()
    {
        cout<<__FUNCTION__<<endl;
    }
    int edges() const       //边
    {
        return e;
    }
    int vertices() const    //顶点
    {
        return v;
    }
    int outDegree(int i)
    {
        if(i<0 || i>=v)
        {
            return 0;
        }
        return h[i].size();
    }
    int inDegree(int i)
    {
        if(i<0 || i>=v)
        {
            return 0;
        }
        int ret = 0;
        for(auto it : h)
        {
            for(auto j : it)
            {
                if(j == i)
                {
                    ++ret;
                }
            }
        }
        return ret;
    }
    bool exist(int i, int j) const 
    {
        return true;
    }
    LinkedGraph<DataType> &add(int i, int j)
    {
        if(i>=0 && i<v && j>=0 && j<v)
        {
            if(find(h[i].begin(), h[i].end(), j) == h[i].end())
            {
                h[i].push_back(j);
                if(!check)
                {
                    h[j].push_back(i);
                }
                ++e;
            }
        }
        return *this;
    }
    LinkedGraph<DataType> &del(int i, int j)
    {
        if(i>=0 && i<v && j>=0 && j<v)
        {
            if(find(h[i].begin(), h[i].end(), j) != h[i].end())
            {
                h[i].erase(find(h[i].begin(), h[i].end(), j));
                if(!check)
                {
                    h[j].erase(find(h[j].begin(), h[j].end(), i));
                }
                --e;
            }
        }
        return *this;
    }
    void print()
    {
        for(int i=0; i<h.size(); ++i)
        {
            for(auto iter : h[i])
            {
                if(iter < i)
                {
                    continue;
                }
                cout << i << "--" << iter << endl;
            }
        }
    }

    /**
     * Synopsis: dfs_recursion 深度优先遍历 递归法
     */
    void dfs_recursion() const 
    {
        vector<bool> flag(v, false);
        dfs_recursion(flag, 0);
        cout<<endl;
    }

    /**
     * Synopsis: dfs_stack 深度优先比遍历 使用栈
     */
    void dfs_stack()
    {
        stack<int> s;
        vector<bool> flag(v, false);
        s.push(0);

        for(;s.size()!=0;)
        {
            int i = s.top();
            flag[i] = true;
            s.pop();
            cout << i << "__";
            for(auto j : h[i])
            {
                if(!flag[j])
                {
                    s.push(j);
                }
            }
        }
        cout << endl;
    }

    /**
     * Synopsis: bfs_queue 广度优先遍历 队列
     */
    void bfs_queue()
    {
        queue<int> q;
        vector<bool> flag(v, false);
        q.push(0);
        for(;q.size()!=0;)
        {
            int i=q.front();
            q.pop();
            flag[i] = true;
            cout << i << "__";
            for(auto j : h[i])
            {
                if(!flag[j])
                {
                    q.push(j);
                }
            }
        }
        cout << endl;
    }

    void topological_sort_in()
    {
        //用来保存输出的顶点
        vector<int> vecCout;

        //先确定各个结点的入度
        vector<int> vecIn(v, 0);
        for(auto it : h)
        {
            for(auto iter : it)
            {
                ++vecIn[iter];
            }
        }
        //cout<<"In"<<" "; for(auto it : vecIn) { cout<<it<<" "; } cout<<endl;
        for(;;)
        {
            int index = -1; 
            for(int i=0; i<v; ++i)
            {
                if(vecIn[i] == 0)
                {
                    index = i;
                    vecCout.push_back(i);       //入度为0 加入输出vec中
                    for(auto it : h[i])         //将该顶点指向的顶点的入度减1
                    {
                        --vecIn[it];
                    }
                    vecIn[i] = -1;              //该顶点入度置为-1
                    break;
                }
            }

            //cout<<"In"<<" "; for(auto it : vecIn) { cout<<it<<" "; } cout<<endl;

            if(index == -1)                     //未找到入度未0的顶点
            {
                break;
            }
        }

        for(auto it : vecCout) { cout<<it<<" "; } cout<<endl;
        for(auto it : vecIn)
        {
            if(it!=-1)
            {
                cout<<"有环"<<endl;
                break;
            }
        }
    }

    void kruskal()
    {
    }

private:
    void dfs_recursion(vector<bool> &flag, int i) const
    {
        cout << i << "__";
        flag[i] = true;
        for(auto it : h[i])
        {
            if(!flag[it])
            {
                dfs_recursion(flag, it);
            }
        }
    }

    int v;
    int e;
    vector<list<DataType>> h;
    map<DataType
    bool check;
};

int main()
{
    /*
     * 0 - 5 - 7 - 6
     * |
     * 2 - 3
     * |
     * 1
     */
    cout<<"main start"<<endl;
    AdjacencyGraphic<int> adjacencyGraphic(8, 0);
    adjacencyGraphic.add(0, 2, 3);
    adjacencyGraphic.add(0, 5, 2);
    adjacencyGraphic.add(2, 3, 1);
    adjacencyGraphic.add(2, 1, 9);
    adjacencyGraphic.add(5, 7, 9);
    adjacencyGraphic.add(7, 6, 9);
    adjacencyGraphic.print();
    cout<<"------------"<<endl;
    //adjacencyGraphic.del(7, 6);
    //adjacencyGraphic.print();
    cout<<"1出度："<<adjacencyGraphic.outDegree(1)<<endl;
    cout<<"3入度："<<adjacencyGraphic.inDegree(3)<<endl;
    cout<<"边个数："<<adjacencyGraphic.edges()<<endl;
    cout<<"顶点个数："<<adjacencyGraphic.vertices()<<endl;
    cout<<"递归深度优先遍历"<<endl;
    adjacencyGraphic.dfs_recursion();
    cout<<"栈深度优先遍历"<<endl;
    adjacencyGraphic.dfs_stack();
    cout<<"广度优先遍历"<<endl;
    adjacencyGraphic.bfs_queue(); 

    cout<<"============"<<endl;

    LinkedGraph<int> linkedGraph(8, false);
    linkedGraph.add(0, 2);
    linkedGraph.add(0, 5);
    linkedGraph.add(2, 3);
    linkedGraph.add(2, 1);
    linkedGraph.add(5, 7);
    linkedGraph.add(7, 6);
    cout<<"------------"<<endl;
    //linkedGraph.del(2, 3);
    cout<<"1出度"<<linkedGraph.outDegree(1)<<endl;
    cout<<"3入度"<<linkedGraph.inDegree(3)<<endl;
    cout<<"边数："<<linkedGraph.edges()<<endl;
    cout<<"顶点数："<<linkedGraph.vertices()<<endl;

    cout<<"递归深度优先遍历"<<endl;
    linkedGraph.dfs_recursion();
    cout<<"栈深度优先遍历"<<endl;
    linkedGraph.dfs_stack(); 
    cout<<"广度优先遍历"<<endl;
    linkedGraph.bfs_queue(); 

    /*
     * 0 ------5 - 7 - 6
     * |       |
     * 2 - 3 - 4
     * |
     * 1
     */

    LinkedGraph<int> linkedGraph_topo(8);
    linkedGraph_topo.add(0, 2);
    linkedGraph_topo.add(0, 5);
    linkedGraph_topo.add(2, 3);
    linkedGraph_topo.add(2, 1);
    linkedGraph_topo.add(3, 4);
    linkedGraph_topo.add(5, 7);
    linkedGraph_topo.add(5, 4);
    linkedGraph_topo.add(7, 6);

    //linkedGraph_topo.add(6, 5);       //加入该边 则有环
    //linkedGraph_topo.print();

    cout<<"拓扑排序"<<endl;
    linkedGraph_topo.topological_sort_in();

    cout<<"main finish"<<endl;
	return 0;
}
