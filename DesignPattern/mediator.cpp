#include <iostream>

using namespace std;

//中介者模式
class Mediator;
class Colleage
{
public:
    ~Colleage() {}
    virtual void Action() = 0;
    virtual void SetState(const string &sdt) = 0;
    virtual string GetState() = 0;
protected:
    Colleage() {}
    Colleage(Mediator *mdt)
    {
        m_pMdt = mdt;
    }
    Mediator *m_pMdt;
};

class Mediator
{
public:
    virtual ~Mediator() {};
    virtual void ActionA() = 0;
    virtual void ActionB() = 0;
protected:
    Mediator() {};
};

class ConcreteMediator : public Mediator
{
public:
    ConcreteMediator() {}
    ConcreteMediator(Colleage *clgA, Colleage *clgB)
    {
        m_pClgA = clgA;
        m_pClgB = clgB;
    }
    ~ConcreteMediator() {}
    void SetConcreteColleageA(Colleage *clgA)
    {
        m_pClgA = clgA;
    }
    void SetConcreteColleageB(Colleage *clgB)
    {
        m_pClgB = clgB;
    }
    Colleage *GetConcreteColleageA()
    {
        return m_pClgA;
    }
    Colleage *GetConcreteColleageB()
    {
        return m_pClgB;
    }
    void IntroColleage(Colleage *clgA, Colleage *clgB)
    {
        m_pClgA = clgA;
        m_pClgB = clgB;
    }
    void ActionA()
    {
        cout<<__FUNCTION__<<" A "<<m_pClgA->GetState()<<endl;
    }
    void ActionB()
    {
        cout<<__FUNCTION__<<" B "<<m_pClgB->GetState()<<endl;
    }
private:
    Colleage * m_pClgA;
    Colleage * m_pClgB;
};


class ConcreteColleageA : public Colleage
{
public:
    ConcreteColleageA() {}
    ConcreteColleageA(Mediator *mdt) : Colleage(mdt)
    {
        ;
    }
    ~ConcreteColleageA() {}
    void Action() 
    {
        m_pMdt->ActionB();
        cout<<"state of ConcreteColleageA:"<<GetState()<<endl;
    }
    void SetState(const string& sdt) 
    {
        m_sSdt = sdt;
    }
    string GetState() 
    {
        return m_sSdt;
    }
private:
    string m_sSdt;
};

class ConcreteColleageB : public Colleage
{
public:
    ConcreteColleageB() {}
    ConcreteColleageB(Mediator *mdt) : Colleage(mdt)
    {
        ;
    }
    ~ConcreteColleageB() {}
    void Action() 
    {
        m_pMdt->ActionA();
        cout<<"state of ConcreteColleageB:"<<GetState()<<endl;
    }
    void SetState(const string& sdt) 
    {
        m_sSdt = sdt;
    }
    string GetState() 
    {
        return m_sSdt;
    }
private:
    string m_sSdt;
};

int main()
{
    ConcreteMediator *m = new ConcreteMediator();

    ConcreteColleageA *ca = new ConcreteColleageA(m);
    ConcreteColleageB *cb = new ConcreteColleageB(m);

    m->IntroColleage(ca, cb);
    m->ActionA();

    ca->SetState("a");
    cb->SetState("b");
    cout<<ca->GetState()<<endl;
    cout<<cb->GetState()<<endl;
    ca->Action();
    cb->Action();

    return 0;
}
