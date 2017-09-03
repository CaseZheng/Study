#include <iostream>

using namespace std;

//装饰模式
class Component 
{
public:
    virtual ~Component()
    {
    }
    virtual void Operation()
    {
    };
protected:
    Component()
    {
    }
};

class ConcreteComponent : public Component
{
public:
    ConcreteComponent()
    {
    }
    ~ConcreteComponent()
    {
    }
    void Operation()
    {
        cout<<"ConcreteComponent  "<<__FUNCTION__<<endl;
    }
};

class Decorator : public Component
{
public:
    Decorator(Component *com)
    {
        m_pCom = com;
    }
    virtual ~Decorator()
    {
        delete m_pCom;
    }
    void Operation()
    {
    }
protected:
    Component *m_pCom;
};

class ConcreteDecorator : public Decorator
{
public:
    ConcreteDecorator(Component *com) : Decorator(com)
    {
    }
    ~ConcreteDecorator()
    {
    }
    void Operation()
    {
        m_pCom->Operation();
        AddedBehavior();
    }
    void AddedBehavior()
    {
        cout<<"ConcreteDecorator "<<__FUNCTION__<<endl;
    }
};

int main()
{
    Component *com = new ConcreteComponent();
    Decorator *dec = new ConcreteDecorator(com);
    dec->Operation();
    delete dec;
    return 0;
}
