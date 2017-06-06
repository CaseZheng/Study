#include "public.h"

class A
{
public:
    A()
    {
        cout<<"A ctor"<<this<<endl;
    }
    A(int _x, int _y) : x(_x), y(_y)
    {
        cout<<"A xy ctor"<<this<<" x:"<<x<<" y:"<<y<<endl;
    }
    ~ A()
    {
        cout<<"A dtor"<<this<<endl;
    }

    void print()
    {
        cout<<"A Print"<<endl;
    }
private:
    int x;
    int y;
};

void TestAutoPtr()
{
    auto_ptr<A> a1(new A());
    cout<<a1.get()<<endl;
    auto_ptr<A> a2 = a1;
    cout<<a1.get()<<endl;
    cout<<a2.get()<<endl;
}

void TestScopedPtr()
{
    scoped_ptr<A> a1(new A());
    cout<<a1.get()<<endl;
    //scoped_ptr<A> a2 = a1;  //错误
    a1->print();
    (*a1).print();
}


class C     //让C代理B，对B的方法做一次封装
{
private:
    class B;
    boost::shared_ptr<B> p;
public:
    C();
    void print();
};

class C::B
{
public:
    void print()
    {
        cout<<"B ctor :"<<this<<endl;
    }
};

C::C():p(new B){}
void C::print()
{
    p->print();
}


class E
{
public:
    E(){cout<<"E ctor"<<endl;}
    virtual void f() = 0;
    virtual void g() = 0;
protected:
    virtual ~E()
    {
        cout<<"E dtor"<<endl;
    }
};
class F : public E
{
public:
    virtual void f()
    {
        cout<<"class F f"<<endl;
    }
    virtual void g()
    {
        cout<<"class F g"<<endl;
    }
};

E* create1()
{
    return (E*)(new F);
}

boost::shared_ptr<E> create2()
{
    return boost::shared_ptr<E>(new F);
}

class G
{
public:
    G()
    {
        cout<<"ctor G :"<<this<<endl;
    }
    ~G()
    {
        cout<<"dtor G :"<<this<<endl;
    }

};

void DeleteG(G *g)
{
    if(g != NULL)
    {
        cout<<"delete G :"<<g<<endl;
        delete g;
    }
}

void AryF(void * p)
{
        cout<<"AryF"<<endl;
}

void TestSharedPtr()
{
    boost::shared_ptr<int> sp1(new int(10));
    cout<<"sp1 unique :"<<sp1.unique()<<endl;
    cout<<"sp1 use_count :"<<sp1.use_count()<<endl;

    boost::shared_ptr<int> sp2(sp1);
    cout<<"sp1 unique :"<<sp1.unique()<<endl;
    cout<<"sp1 use_count :"<<sp1.use_count()<<endl;
    cout<<"sp2 unique :"<<sp2.unique()<<endl;
    cout<<"sp2 use_count :"<<sp2.use_count()<<endl;

    sp2.reset();
    cout<<"sp2 reset after"<<endl;
    cout<<"sp1 unique :"<<sp1.unique()<<endl;
    cout<<"sp1 use_count :"<<sp1.use_count()<<endl;
    cout<<"sp2 unique :"<<sp2.unique()<<endl;
    cout<<"sp2 use_count :"<<sp2.use_count()<<endl;

    boost::shared_ptr<A> spA1(new A());
    cout<<"spA :"<<spA1.get()<<endl;
    
    //工厂函数
    boost::shared_ptr<A> spA2 = boost::make_shared<A>();

    boost::shared_ptr<A> spA3 = boost::make_shared<A, int, int>(1, 2);

    //应用于标准容器
    vector<boost::shared_ptr<int>> v(3);
    int i = 0;
    for(auto& it : v)
    {
        it = boost::make_shared<int>(++i);
        cout<<*(it)<<endl;
    }

    boost::shared_ptr<int> sp3 = v[2];
    *sp3 = 100;
    cout<<*v[2]<<endl;

    //应用于桥接模式
    C c;
    c.print();

    {
        //应用于工厂模式
        E * E1 = create1();
        boost::shared_ptr<E> E2 = create2();

        delete (F*)E1;              //E1必须手动调用delete 而E2在出作用域后自动调用 E的析构函数是protected的，所需需要转型为F再delete
    }
    cout<<"桥接模式结束"<<endl;

    //定制删除器
    boost::shared_ptr<G> pg(new G(), DeleteG);

    boost::shared_ptr<void> pv(NULL, AryF);
}

class H : public boost::enable_shared_from_this<H>
{
public:
    H(int _n) : n(_n)
    {
        cout<<"H ctor"<<endl;
    }
    void print()
    {
        cout<<"H n:"<<n<<endl;
    }
    int n;
};

void TestWeakPtr()
{
    boost::shared_ptr<int> sp1(new int(10));
    cout<<"sp1 use_count:"<<sp1.use_count()<<endl;
    boost::weak_ptr<int> wp1(sp1);
    cout<<"sp1 use_count:"<<sp1.use_count()<<endl;
    cout<<"wp1 use_count:"<<wp1.use_count()<<endl;

    if(!wp1.expired())
    {
        boost::shared_ptr<int> sp2 = wp1.lock();
        cout<<"sp1 use_count:"<<sp1.use_count()<<endl;
        cout<<"sp2 use_count:"<<sp2.use_count()<<endl;
    }
    cout<<"sp1 use_count:"<<sp1.use_count()<<endl;
    sp1.reset();

    cout<<"wp1 use_count:"<<wp1.use_count()<<endl;

    boost::shared_ptr<H> sh = boost::make_shared<H>(314);
    sh->print();
    boost::shared_ptr<H> sh2 = sh->shared_from_this();
    sh->n = 1000;
    sh2->print();
    sh->print();
}


int main()
{
    cout<<"main start"<<endl;

    //auto_ptr
    //TestAutoPtr();

    //scoped_ptr
    //TestScopedPtr();

    //shared_ptr
    //TestSharedPtr();

    //weak_ptr
    TestWeakPtr();
    
    cout<<"main finish"<<endl;
	return 0;
}

