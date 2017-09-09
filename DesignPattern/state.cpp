#include <iostream>

using namespace std;

//状态模式
class State;
class Context;
class ConcreteStateA;
class ConcreteStateB;

class State
{
public:
    State()
    {
        ;
    }
    virtual ~State()
    {
        ;
    }
    virtual void OperationInterface(Context *) = 0;
    virtual void OperationChangeState(Context *) = 0;
protected:
    bool ChangeState(Context *con, State *st);
};


void State::OperationInterface(Context *con)
{
    cout<<"State::.."<<endl;
}

class ConcreteStateA : public State
{
public:
    ConcreteStateA()
    {
        ;
    }
    virtual ~ConcreteStateA()
    {
        ;
    }
    virtual void OperationInterface(Context *con)
    {
        cout<<"ConcreteStateA::OperationInterface..."<<endl;
    }
    virtual void OperationChangeState(Context *con);
};

class ConcreteStateB : public State
{
public:
    ConcreteStateB()
    {
        ;
    }
    virtual ~ConcreteStateB()
    {
        ;
    }
    virtual void OperationInterface(Context *con)
    {
        cout<<"ConcreteStateB::OperationInterface..."<<endl;
    }
    virtual void OperationChangeState(Context *con)
    {
        OperationInterface(con);
        ChangeState(con, new ConcreteStateA());
    }
};

class Context
{
public:
    Context()
    {
        ;
    }
    Context(State *state)
    {
        m_State = state;
    }
    ~Context()
    {
        delete m_State;
    }
    void OperationInterface()
    {
        m_State->OperationInterface(this);
    }
    void OperationChangeState()
    {
        m_State->OperationChangeState(this);
    }
    bool ChangeState(State *state)
    {
        m_State = state;
        return true;
    }
private:
    State *m_State;

friend class State;
};

bool State::ChangeState(Context *con, State *st)
{
    con->ChangeState(st);
}

void ConcreteStateA::OperationChangeState(Context *con)
{
    OperationInterface(con);
    ChangeState(con, new ConcreteStateB());
}

int main()
{
    State *st = new ConcreteStateA();
    Context *con = new Context(st);
    con->OperationChangeState();
    con->OperationChangeState();
    con->OperationChangeState();
    con->OperationChangeState();
    con->OperationChangeState();
    con->OperationChangeState();

    return 0;
}
