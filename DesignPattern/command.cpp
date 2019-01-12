#include <iostream>

using namespace std;

//命令模式
class Reciever
{
public:
    Reciever() {};
    virtual ~Reciever() {};
    virtual void Action() = 0;
};

class RecieverA : public Reciever
{
public:
    RecieverA() {};
    virtual ~RecieverA() {};
    void Action()
    {
        cout<<__FUNCTION__<<"  A"<<endl;
    }
};

class RecieverB : public Reciever
{
public:
    RecieverB() {};
    virtual ~RecieverB() {};
    void Action()
    {
        cout<<__FUNCTION__<<"  B"<<endl;
    }
};


class Command 
{
public:
    virtual ~Command() {};
    virtual void Excute() = 0;
protected:
    Command(){};
};

class ConcreteCommand : public Command 
{
public:
    ConcreteCommand(Reciever *rec)
    {
        m_pRev = rec;
    }
    ~ConcreteCommand() 
    {
        delete m_pRev;
    }
    void Excute()
    {
        m_pRev->Action();
        cout<<__FUNCTION__<<endl;
    }
private:
    Reciever *m_pRev;
};

class Invoker
{
public:
    Invoker(Command* cmd)
    {
        m_pCmd = cmd;
    }
    ~Invoker()
    {
        delete m_pCmd;
    }
    void Invoke()
    {
        m_pCmd->Excute();
    }
private:
    Command *m_pCmd;
};

int main()
{
    Reciever *reva = new RecieverA();
    Command *cmda = new ConcreteCommand(reva);
    Invoker *inva = new Invoker(cmda);
    inva->Invoke();
    Reciever *revb = new RecieverB();
    Command *cmdb = new ConcreteCommand(revb);
    Invoker *invb = new Invoker(cmdb);
    invb->Invoke();

    return 0;
}
