#include <iostream>

using namespace std;

//桥梁模式
class AbstractionImp;

class Abstraction
{
public:
    virtual ~Abstraction() {};
    virtual void Operation() = 0;
protected:
    Abstraction() {};
};

class AbstractionImp
{
public:
    virtual ~AbstractionImp() {}
    virtual void Operation() = 0;
protected:
    AbstractionImp() {}
};

void AbstractionImp::Operation()
{
    cout<<"IMP"<<__FUNCTION__<<endl;
}


class RefinedAbstraction : public Abstraction
{
public:
    RefinedAbstraction(AbstractionImp *imp)
    {
        m_pImp = imp;
    }
    ~RefinedAbstraction() {}
    void Operation()
    {
        m_pImp->Operation();
    }
private:
    AbstractionImp *m_pImp;
};

class ConcreteAbstractionImpA : public AbstractionImp
{
public:
    ConcreteAbstractionImpA() {}
    ~ConcreteAbstractionImpA() {}
    virtual void Operation() 
    {
        cout<<"A"<<__FUNCTION__<<endl;
    }
};

class ConcreteAbstractionImpB : public AbstractionImp
{
public:
    ConcreteAbstractionImpB() {}
    ~ConcreteAbstractionImpB() {}
    virtual void Operation() 
    {
        cout<<"B"<<__FUNCTION__<<endl;
    }
};

int main()
{
    AbstractionImp *impa = new ConcreteAbstractionImpA();
    Abstraction *absa = new RefinedAbstraction(impa);
    absa->Operation();

    AbstractionImp *impb = new ConcreteAbstractionImpB();
    Abstraction *absb = new RefinedAbstraction(impb);
    absb->Operation();
    return 0;
}
