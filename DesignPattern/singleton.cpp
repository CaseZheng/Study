#include <iostream>

using namespace std;

//常见的单例模式
class SingletonOne
{
private:
    SingletonOne()
    {
        cout<<__FUNCTION__<<endl;
    }
    SingletonOne(const SingletonOne &right);
    SingletonOne & operator=(const SingletonOne &right);
    static SingletonOne _instance;
public:
    static SingletonOne& Instance()
    {
        return _instance;
    };
    ~SingletonOne()
    {
        cout<<__FUNCTION__<<endl;
    }
    void print()
    {
        cout<<__FUNCTION__<<endl;
    };
};
SingletonOne SingletonOne::_instance;

class SingletonTwo
{
private:
    SingletonTwo()
    {
        cout<<__FUNCTION__<<endl;
    }
    SingletonTwo(const SingletonTwo &right);
    SingletonTwo & operator=(const SingletonTwo &right);
    static SingletonTwo *_instance;
public:
    static SingletonTwo* Instance()
    {
        if( nullptr == _instance )
        {
            _instance = new SingletonTwo();
        }
        return _instance;
    };
    ~SingletonTwo()
    {
        cout<<__FUNCTION__<<endl;
    }
    void print()
    {
        cout<<__FUNCTION__<<endl;
    };
};
SingletonTwo* SingletonTwo::_instance = nullptr;

template <class T>
class SingletonThree
{
private:
    SingletonThree(){}
    SingletonThree(const SingletonThree &right);
    SingletonThree & operator=(const SingletonThree &right);
    static T _instance;
public:
    static T& Instance()
    {
        return _instance;
    };
    virtual ~SingletonThree(){}
};

template <class T>
T SingletonThree<T>::_instance;

class A 
{
public:
    A()
    {
        cout<<__FUNCTION__<<endl;
    }
    virtual ~A()
    {
        cout<<__FUNCTION__<<endl;
    }
    void print()
    {
        cout<<__FUNCTION__<<endl;
    }
};
typedef SingletonThree<A> SingletonA;   //SingletonA

int main()
{
    //SingletonOne::Instance().print();
    //SingletonTwo::Instance()->print();
    SingletonA::Instance().print();
    return 0;
}
