#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "public.h"

using namespace std;

/*
合并 k 个排序链表，返回合并后的排序链表。请分析和描述算法的复杂度。
示例:
输入:
[
  1->4->5,
  1->3->4,
  2->6
]
输出: 1->1->2->3->4->4->5->6
*/

struct ListNodeIndex
{
    ListNodeIndex(ListNode *pNode, int index) : m_pNode(pNode), m_iIndex(index){}
    ListNode *m_pNode;
    int m_iIndex;
};


struct ListNodeGreater : public binary_function<ListNodeIndex, ListNodeIndex, bool>
{ 
    bool operator()(const ListNodeIndex &_Left, const ListNodeIndex &_Right) const
    { 
        return (_Left.m_pNode->val > _Right.m_pNode->val);
    }
}; 

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        vector<ListNodeIndex> vecList;
        for(int i=0; i<lists.size(); ++i)
        {
            ListNode *pHead = lists[i];
            if(NULL == pHead)
            {
                continue;
            }
            ListNode *pNext = pHead->next;
            lists[i] = pNext;
            vecList.push_back(ListNodeIndex{pHead, i});
        }
        ListNode *pRet = NULL;
        ListNode *pTail = NULL;
        make_heap(vecList.begin(), vecList.end(), ListNodeGreater());
        while(!vecList.empty())
        {
            for(auto &it : vecList)
            {
                cout << it.m_pNode->val << " ";
            }
            cout << endl;

            int iIndex = vecList.front().m_iIndex;
            if(pRet == NULL)
            {
                pRet = pTail = vecList.front().m_pNode;
            }
            else
            {
                pTail = pTail->next = vecList.front().m_pNode;
            }
            cout << vecList.front().m_pNode->val << endl;
            pop_heap(vecList.begin(), vecList.end(), ListNodeGreater());
            vecList.pop_back();

            if(NULL != lists[iIndex])
            {
                ListNode *pHead = lists[iIndex];
                ListNode *pNext = pHead->next;
                lists[iIndex] = pNext;
                vecList.push_back(ListNodeIndex{pHead, iIndex});
                push_heap(vecList.begin(), vecList.end(), ListNodeGreater());
            }
        }
        return pRet;
    }
};

int main()
{
    ListNode *pHead1 = NULL;
    ListNode *pHead2 = NULL;
    ListNode *pHead3 = NULL;
    ListNode *pTail = NULL;
    ListNode *pTmp = new ListNode(1);
    pHead1 = pTail = pTmp;
    pTmp = new ListNode(4);
    pTail = pTail->next = pTmp;
    pTmp = new ListNode(5);
    pTail = pTail->next = pTmp;

    pTmp = new ListNode(1);
    pHead2 = pTail = pTmp;
    pTmp = new ListNode(3);
    pTail = pTail->next = pTmp;
    pTmp = new ListNode(4);
    pTail = pTail->next = pTmp;

    pTmp = new ListNode(2);
    pHead3 = pTail = pTmp;
    pTmp = new ListNode(6);
    pTail = pTail->next = pTmp;

    printList(pHead1);
    printList(pHead2);
    printList(pHead3);
    vector<ListNode *> vecList;
    vecList.push_back(pHead1);
    vecList.push_back(pHead2);
    vecList.push_back(pHead3);

    ListNode *pRet = Solution().mergeKLists(vecList);
    printList(pRet);

    for(auto &it : vecList)
    {
        freeList(it);
    }

    return 0;
}
