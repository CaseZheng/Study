#include <iostream>

using namespace std;

class Subsystem1
{
public:
    Subsystem1()
    {
    }
    ~Subsystem1()
    {
    }
    void Operation()
    {
        cout<<"Subsystem1 "<<__FUNCTION__<<endl;
    }
};

class Subsystem2
{
public:
    Subsystem2()
    {
    }
    ~Subsystem2()
    {
    }
    void Operation()
    {
        cout<<"Subsystem2 "<<__FUNCTION__<<endl;
    }
};

class Facade
{
public:
    Facade()
    {
        m_pSub1 = new Subsystem1();
        m_pSub2 = new Subsystem2();
    }
    ~Facade()
    {
        delete m_pSub1;
        delete m_pSub2;
    }
    void Operation()
    {
        cout<<"Facade "<<__FUNCTION__<<endl;
        m_pSub1->Operation();
        m_pSub2->Operation();
    }
private:
    Subsystem1 *m_pSub1;
    Subsystem2 *m_pSub2;
};

int main()
{
    Facade fac;
    fac.Operation();
    return 0;
}
