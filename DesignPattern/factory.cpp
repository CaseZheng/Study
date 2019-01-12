#include <iostream>

using namespace std;

//工厂模式
class Product
{
public:
    virtual ~Product(){};
protected:
    Product(){};
};

class ConcreteProduct:public Product
{
public:
    ConcreteProduct()
    {
        cout<<__FUNCTION__<<endl;
    }
    ~ConcreteProduct()
    {
    };
};

class Factory
{
public:
    virtual ~Factory(){};
    virtual void* CreateProduct() = 0;
protected:
    Factory(){};
};

class ConcreteFactory:public Factory
{
public:
    ConcreteFactory()
    {
        cout<<__FUNCTION__<<endl;
    }
    ~ConcreteFactory()
    {
    }
    void* CreateProduct()
    {
        return new ConcreteProduct();
    }
};

int main()
{
    Factory *fac = new ConcreteFactory();
    Product *p = (Product*)fac->CreateProduct();
    return 0;
}
