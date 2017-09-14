#include <iostream>
#include <list>
#include <string>

using namespace std;

typedef string State;

class Observer;

class Subject
{
public:
    virtual ~Subject()
    {
    }

    virtual void Attach(Observer *obv)
    {
        m_lObvs.push_front(obv);
    }
    virtual void Detach(Observer *obv)
    {
        if(obv != NULL)
        {
            m_lObvs.remove(obv);
        }
    }
    virtual void Notify();
    virtual void SetState(const State &st) = 0;
    virtual State GetState() = 0;
protected:
    Subject()
    {
    }
private:
    list<Observer *> m_lObvs;
};


class ConcreteSubject : public Subject
{
public:
    ConcreteSubject()
    {
    }
    ~ConcreteSubject()
    {
    }
    State GetState()
    {
        return m_sSt;
    }
    void SetState(const State& st)
    {
        m_sSt = st;
        Notify();
    }
private:
    State m_sSt;
};

class Observer
{
public:
    virtual ~Observer()
    {
    }
    virtual void Update(Subject *sub) = 0;
    virtual void PrintInfo() = 0;
protected:
    Observer()
    {
    }
    State m_sSt;
};

class ConcreteObserverA : public Observer
{
public:
    virtual Subject *GetSubject()
    {
        return m_pSub;
    }
    ConcreteObserverA(Subject *sub)
    {
        m_pSub = sub;
        m_pSub->Attach(this);
    }
    virtual ~ConcreteObserverA()
    {
        m_pSub->Detach(this);
    }
    void Update(Subject *sub)
    {
        m_sSt = m_pSub->GetState();
        PrintInfo();
    }
    void PrintInfo()
    {
        cout<<"A  "<<m_pSub->GetState()<<endl;
    }
private:
    Subject *m_pSub;
};

class ConcreteObserverB : public Observer
{
public:
    virtual Subject *GetSubject()
    {
        return m_pSub;
    }
    ConcreteObserverB(Subject *sub)
    {
        m_pSub = sub;
        m_pSub->Attach(this);
    }
    virtual ~ConcreteObserverB()
    {
        m_pSub->Detach(this);
    }
    void Update(Subject *sub)
    {
        m_sSt = m_pSub->GetState();
        PrintInfo();
    }
    void PrintInfo()
    {
        cout<<"B  "<<m_pSub->GetState()<<endl;
    }
private:
    Subject *m_pSub;
};

void Subject::Notify()
{
    for(auto pObv : m_lObvs)
    {
        if(pObv != NULL)
        {
            pObv->Update(this);
        }
    }
}

int main()
{
    ConcreteSubject *sub = new ConcreteSubject();
    Observer *o1 = new ConcreteObserverA(sub);
    sub->SetState("state1");
    Observer *o2 = new ConcreteObserverB(sub);
    sub->SetState("state2");
    sub->SetState("state3");

    delete o1;
    delete o2;
    delete sub;

    return 0;
}
