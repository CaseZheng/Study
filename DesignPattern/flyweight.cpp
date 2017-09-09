#include <iostream>
#include <vector>

using namespace std;

//享元模式
class Flyweight 
{
public:
    virtual ~Flyweight()
    {
        ;
    }
    virtual void Operation(const string &extrinsicState)
    {
        ;
    }
    string GetIntrinsicState()
    {
        return m_sIntrinsicState;
    }
protected:
    Flyweight(string intrinsicState)
    {
        m_sIntrinsicState = intrinsicState;
    }
private:
    string m_sIntrinsicState;
};

class ConcreteFlyweight : public Flyweight
{
public:
    ConcreteFlyweight(string intrinsicState) : Flyweight(intrinsicState)
    {
        cout<<"ConcreteFlyweight Build ...."<<intrinsicState<<endl;
    }
    ~ConcreteFlyweight()
    {
        ;
    }
    void Operation(const string &extrinsicState)
    {
        cout<<"ConcreteFlyweight:内"<<GetIntrinsicState()<<"外"<<extrinsicState<<endl;;
    }
};

class FlyweightFactory
{
public:
    FlyweightFactory()
    {
        ;
    }
    ~FlyweightFactory()
    {
        ;
    }
    Flyweight *GetFlywgight(const string &key)
    {
        //auto it = m_vFly.begin();
        //for(; it!=m_vFly.end(); ++it)
        //{
            //if((*it)->GetIntrinsicState() == key)
            //{
                //cout<<"already creteed by users ..."<<key<<endl;
                //return *it;
            //}
        //}
        for(auto it:m_vFly)
        {
            if(it->GetIntrinsicState() == key)
            {
                cout<<"already creteed by users ..."<<key<<endl;
                return it;
            }
        }
        Flyweight *fn = new ConcreteFlyweight(key);
        m_vFly.push_back(fn);
        return fn;
    }
private:
    vector<Flyweight*> m_vFly;
};

int main()
{
    FlyweightFactory fc;
    Flyweight *fw1 = fc.GetFlywgight("hello");
    cout<<fw1->GetIntrinsicState()<<endl;
    Flyweight *fw2 = fc.GetFlywgight("world");
    cout<<fw2->GetIntrinsicState()<<endl;
    Flyweight *fw3 = fc.GetFlywgight("hello");
    cout<<fw3->GetIntrinsicState()<<endl;

    return 0;
}
