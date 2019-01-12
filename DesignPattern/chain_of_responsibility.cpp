#include <iostream>

using namespace std;

//责任链模式
class Handle
{
public:
    virtual ~Handle()
    {
        delete m_pSucc;
    }
    virtual void HandleRequest() = 0;
    void SetSuccessor(Handle *succ)
    {
        m_pSucc = succ;
    }
    Handle *GetSuccessor()
    {
        return m_pSucc;
    }
protected:
    Handle()
    {
        m_pSucc = nullptr;
    }
    Handle(Handle *succ)
    {
    }
private:
    Handle *m_pSucc;
};

class ConcreteHandleA : public Handle
{
public:
    ConcreteHandleA()
    {
    }
    ~ConcreteHandleA()
    {
    }
    ConcreteHandleA(Handle *succ) : Handle(succ)
    {
    }
    void HandleRequest()
    {
        if(GetSuccessor() != 0)
        {
            cout<<"ConcreteHandleA next"<<endl;
            GetSuccessor()->HandleRequest();
        }
        else
        {
            cout<<"ConcreteHandleA process"<<endl;
        }
    }
};

class ConcreteHandleB : public Handle
{
public:
    ConcreteHandleB()
    {
    }
    ~ConcreteHandleB()
    {
    }
    ConcreteHandleB(Handle *succ) : Handle(succ)
    {
    }
    void HandleRequest()
    {
        if(GetSuccessor() != 0)
        {
            cout<<"ConcreteHandleB next"<<endl;
            GetSuccessor()->HandleRequest();
        }
        else
        {
            cout<<"ConcreteHandleB process"<<endl;
        }
    }
};

int main()
{
    Handle *h1 = new ConcreteHandleA();
    Handle *h2 = new ConcreteHandleB();
    h1->SetSuccessor(h2);
    h1->HandleRequest();

    return 0;
}
