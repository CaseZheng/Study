#include <iostream>

using namespace std;

class Strategy
{
public:
    Strategy()
    {
    }
    virtual ~Strategy()
    {
        cout<<__FUNCTION__<<endl;
    }
    virtual void AlgrithmInterface() = 0;
};

class StrategyA : public Strategy
{
public:
    StrategyA()
    {
    }
    virtual ~StrategyA()
    {
        cout<<__FUNCTION__<<endl;
    }
    void AlgrithmInterface()
    {
        cout<<"A "<<__FUNCTION__<<endl;
    }
};

class StrategyB : public Strategy
{
public:
    StrategyB()
    {
    }
    virtual ~StrategyB()
    {
        cout<<__FUNCTION__<<endl;
    }
    void AlgrithmInterface()
    {
        cout<<"B "<<__FUNCTION__<<endl;
    }
};

class Context
{
public:
    Context(Strategy *stg)
    {
        SetStg(stg);
    }
    ~Context()
    {
        if(m_pStg != nullptr)
        {
            delete m_pStg;
        }
    }
    void DoAction()
    {
        if(m_pStg != nullptr)
        {
            m_pStg->AlgrithmInterface();
        }
    }
    void SetStg(Strategy *stg)
    {
        if(m_pStg != nullptr)
        {
            delete m_pStg;
            m_pStg = nullptr;
        }
        m_pStg = stg;
    }
private:
    Strategy *m_pStg;
};

int main()
{
    Context *pc = new Context(new StrategyA());
    pc->DoAction();
    pc->SetStg(new StrategyB());
    pc->DoAction();
    if(pc != nullptr)
    {
        delete pc;
        pc = nullptr;
    }

    return 0;
}
