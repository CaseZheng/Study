#include <iostream>

using namespace std;

class Basic 
{
public:
    Basic()
    {
        cout << "Basic" << endl;
    }
    virtual ~Basic()
    {
        cout << "~Basic" << endl;
    }
};

class Child : public Basic
{
public:
    Child()
    {
        cout << "Child" << endl;
    }
    virtual ~Child()
    {
        cout << "~Child" << endl;
    }
};

int main()
{
    cout << sizeof(Basic) << endl;
    cout << sizeof(Child) << endl;

    Child *pC = new Child();
    Basic *pB = dynamic_cast<Basic*>(pC);
    delete pB;
    return 0;
}
