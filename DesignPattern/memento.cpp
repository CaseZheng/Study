#include <iostream>

using namespace std;

typedef string State;

class Originator;

class Memento
{
public:
    friend class Originator;

    Memento();
    Memento(const State &sdt);
    ~Memento()
    {
    }
    void SetState(const State &sdt);
    State GetState();
private:
    State m_sSdt;
};

Memento::Memento()
{
}

Memento::Memento(const State &sdt)
{
    m_sSdt = sdt;
}

State Memento::GetState()
{
    return m_sSdt;
}

void Memento::SetState(const State &sdt)
{
    m_sSdt = sdt;
}


class Originator
{
public:
    Originator()
    {
        m_sSdt = "";
        m_pMt = nullptr;
    }
    Originator(const State &sdt)
    {
        m_sSdt = sdt;
        m_pMt = nullptr;
    }
    ~Originator()
    {
    }
    Memento *CreateMemento()
    {
        return new Memento(m_sSdt);
    }
    void RestoreToMemento(Memento *mt)
    {
        m_sSdt = mt->GetState();
    }
    State GetState()
    {
        return m_sSdt;
    }
    void SetState(const State &sdt)
    {
        m_sSdt = sdt;
    }
    void PrintState()
    {
        cout<<"Originator "<<__FUNCTION__<<" "<<m_sSdt<<endl;
    }
private:
    State m_sSdt;
    Memento *m_pMt;
};


int main()
{
    Originator *o = new Originator();
    o->SetState("old");
    o->PrintState();
    Memento *m = o->CreateMemento();
    o->SetState("new");
    o->PrintState();
    o->RestoreToMemento(m);
    o->PrintState();
    return 0;
}
