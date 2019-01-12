#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Component
{
public:
    Component()
    {
    }
    virtual ~Component()
    {
    }
public:
    virtual void Operation() = 0;
    virtual void Add(const Component *com)
    {
    }
    virtual void Remove(const Component *com)
    {
    }
    virtual Component* GetChild(int)
    {
        return nullptr;
    }
};

class Componsite : public Component
{
public:
    Componsite()
    {
    }
    ~Componsite()
    {
    }
public:
    void Operation()
    {
        cout<<"Componsite "<<__FUNCTION__<<endl;
        for(auto it : m_vCom)
        {
            it->Operation();        //调用下一层节点的方法
        }
    }
    void Add(Component *com)
    {
        m_vCom.push_back(com);
    }
    void Remove(Component *com)
    {
        auto it = find(m_vCom.begin(), m_vCom.end(), com);
        if(it != m_vCom.end())
        {
            m_vCom.erase(it);
        }
    }
    Component* GetChild(int index)
    {
        if(index >= m_vCom.size())
        {
            return nullptr;
        }
        return m_vCom[index];
    }
private:
    vector<Component*> m_vCom;
};

class Leaf : public Component
{
public:
    Leaf()
    {
    }
    ~Leaf()
    {
    }
    void Operation()
    {
        cout<<"Leaf "<<__FUNCTION__<<endl;
    }
};

int main()
{
    Leaf *l = new Leaf();
    l->Operation();
    Componsite *com = new Componsite();
    com->Add(l);
    com->Operation();
    Component *ll = com->GetChild(0);
    ll->Operation();
    return 0;
}
