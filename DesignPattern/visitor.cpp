#include <iostream>

using namespace std;

//访问者模式
class ConcreteElementA;
class ConcreteElementB;
class Element;

class Visitor
{
public:
    virtual ~Visitor()
    {
    }
    virtual void VisitConcreteElementA(Element *elm) = 0;
    virtual void VisitConcreteElementB(Element *elm) = 0;
protected:
    Visitor()
    {
    }
};

class ConcreteVisitorA : public Visitor
{
public:
    ConcreteVisitorA()
    {
    }
    virtual ~ConcreteVisitorA()
    {
    }
    virtual void VisitConcreteElementA(Element *elm)
    {
        cout<<__FUNCTION__<<"  i will visit ConcreteElementA..."<<endl;
    }
    virtual void VisitConcreteElementB(Element *elm)
    {
        cout<<__FUNCTION__<<"  i will visit ConcreteElementB..."<<endl;
    }
};

class ConcreteVisitorB : public Visitor
{
public:
    ConcreteVisitorB()
    {
    }
    virtual ~ConcreteVisitorB()
    {
    }
    virtual void VisitConcreteElementA(Element *elm)
    {
        cout<<__FUNCTION__<<"  i will visit ConcreteElementA..."<<endl;
    }
    virtual void VisitConcreteElementB(Element *elm)
    {
        cout<<__FUNCTION__<<"  i will visit ConcreteElementB..."<<endl;
    }
};

class Element 
{
public:
    virtual ~Element()
    {
    }
    virtual void Accept(Visitor *vis) = 0;
protected:
    Element()
    {
    }
};

class ConcreteElementA : public Element
{
public:
    ConcreteElementA()
    {
    }
    ~ConcreteElementA()
    {
    }
    void Accept(Visitor *vis)
    {
        cout<<"visiting ConcreteElementA..."<<endl;
        vis->VisitConcreteElementA(this);
    }
};
class ConcreteElementB : public Element
{
public:
    ConcreteElementB()
    {
    }
    ~ConcreteElementB()
    {
    }
    void Accept(Visitor *vis)
    {
        cout<<"visiting ConcreteElementB..."<<endl;
        vis->VisitConcreteElementB(this);
    }
};

int main()
{
    Visitor *visa = new ConcreteVisitorA();
    Element *elma = new ConcreteElementA();
    elma->Accept(visa);

    Visitor *visb = new ConcreteVisitorB();
    Element *elmb = new ConcreteElementB();
    elmb->Accept(visb);
    return 0;
}
