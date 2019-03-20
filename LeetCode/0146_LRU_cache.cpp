#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <list>

using namespace std;

/*
运用你所掌握的数据结构，设计和实现一个  LRU (最近最少使用) 缓存机制。它应该支持以下操作： 获取数据 get 和 写入数据 put 。
获取数据 get(key) - 如果密钥 (key) 存在于缓存中，则获取密钥的值（总是正数），否则返回 -1。
写入数据 put(key, value) - 如果密钥不存在，则写入其数据值。当缓存容量达到上限时，它应该在写入新数据之前删除最近最少使用的数据值，从而为新的数据值留出空间。

进阶:
你是否可以在 O(1) 时间复杂度内完成这两种操作？

示例:
LRUCache cache(2);	//缓存容量
cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // 返回  1
cache.put(3, 3);    // 该操作会使得密钥 2 作废
cache.get(2);       // 返回 -1 (未找到)
cache.put(4, 4);    // 该操作会使得密钥 1 作废
cache.get(1);       // 返回 -1 (未找到)
cache.get(3);       // 返回  3
cache.get(4);       // 返回  4
*/

class LRUCache {
public:
    struct Value
    {
        Value() {}
        Value(int value, list<int>::iterator it) : m_iValue(value), m_it(it) {}
        int m_iValue;
        list<int>::iterator m_it;
    };

    LRUCache(int capacity) : m_hash(capacity), m_iCapacity(capacity)
 	{
    }
    
    int get(int key) {
        auto it=m_hash.begin();
        if((it=m_hash.find(key)) != m_hash.end())
        {
            m_list.erase(it->second.m_it);
            m_list.push_front(it->first);
            it->second.m_it = m_list.begin();
            return it->second.m_iValue;
        }
        else 
        {
            return -1;
        }
    }
    
    void put(int key, int value)
    {
        auto it=m_hash.begin();
        if((it=m_hash.find(key)) != m_hash.end())
        {
            m_list.erase(it->second.m_it);
            m_list.push_front(key);
            it->second.m_iValue = value;
            it->second.m_it = m_list.begin();
            return;
        }
        if(m_hash.size() >= m_iCapacity)
        {
            auto it = m_hash.find(m_list.back());
            m_list.erase(it->second.m_it);
            m_hash.erase(it);
        }
        m_list.push_front(key);
        Value oValue(value, m_list.begin());
        m_hash[key] = oValue;
    }

private:
	unordered_map<int, Value> m_hash;
    list<int> m_list;
    int m_iCapacity;
};

int main()
{
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    cout << cache.get(1) << endl; // 返回  1
    cache.put(3, 3);              // 该操作会使得密钥 2 作废
    cout << cache.get(2) << endl; // 返回 -1 (未找到)
    cache.put(4, 4);              // 该操作会使得密钥 1 作废
    cout << cache.get(1) << endl; // 返回 -1 (未找到)
    cout << cache.get(3) << endl; // 返回  3
    cout << cache.get(4) << endl; // 返回  4
    return 0;
}
