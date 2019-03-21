#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "public.h"

using namespace std;
/*
在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序。

示例 1:

输入: 4->2->1->3
输出: 1->2->3->4

示例 2:

输入: -1->5->3->4->0
输出: -1->0->3->4->5

插入,选择,冒泡的时间复杂度是都O(n^2)可以排除
O(n log n)时间复杂度的排序算法:快速排序,归并排序,堆排序
符合O(n log n)时间复杂读和常数级空间复杂度的算法:快速排序,归并排序.
堆排序在对数组排序的时候空间复杂度为O(1),但对链表排序需要开辟数组空间所以时间复杂度为O(n)
*/

class Solution {
public:
    ListNode* sortList(ListNode* head) {
        //return sortListQuickSort(head);
        return sortListQuickSortUnRecur(head);
    }

    ListNode* sortListQuickSortUnRecur(ListNode *head)
    {
        return pRet;
    }

    ListNode* sortListQuickSort(ListNode *head)
    {
        ListNode *pTail = NULL;
        return sortListQuickSort(head, pTail);
    }
    //递归算法 栈会溢出
    ListNode* sortListQuickSort(ListNode *head, ListNode* &pTail)
    {
        if(NULL == head)
        {
            return head;
        }
        ListNode *pDivision = head;
        ListNode *pNewHead = head->next;
        pDivision->next = NULL;
        if(NULL == pNewHead)
        {
            pTail = head;
            return head;
        }
        ListNode *pLeft = NULL;
        ListNode *pLeftTail = NULL;
        ListNode *pRight = NULL;
        ListNode *pRightTail = NULL;
        while(NULL != pNewHead)
        {
            cout << pNewHead->val << endl;
            if(pNewHead->val <= pDivision->val)
            {
                if(pLeft == NULL)
                {
                    pLeft = pLeftTail = pNewHead;
                }
                else
                {
                    pLeftTail->next = pNewHead;
                    pLeftTail = pNewHead;
                }
                pNewHead = pNewHead->next;
                pLeftTail->next = NULL;
            }
            else
            {
                if(pRight == NULL)
                {
                    pRight = pRightTail = pNewHead;
                }
                else
                {
                    pRightTail->next = pNewHead;
                    pRightTail = pNewHead;
                }
                pNewHead = pNewHead->next;
                pRightTail->next = NULL;
            }
        }
        pLeftTail = pRightTail = NULL;
        pLeft = sortListQuickSort(pLeft, pLeftTail);
        pRight = sortListQuickSort(pRight, pRightTail);
        ListNode *pRet = NULL;
        if(pLeft!=NULL)
        {
            pRet = pLeft;
            pLeftTail->next = pDivision;
            pDivision->next = pRight;
        }
        else
        {
            pRet = pDivision;
            pDivision->next = pRight;
        }
        if(pRight!=NULL)
        {
            pTail = pRightTail;
        }
        else
        {
            pTail = pDivision;
        }
        return pRet;
    }

    ListNode* sortListMergeSort(ListNode *head)
    {
        return NULL;
    }
};

int main()
{
    ListNode *pHead = NULL;
    ListNode *pTail = NULL;
    ListNode *pTmp = new ListNode(5);
    pHead = pTail = pTmp;
    pTmp = new ListNode(3);
    pTail = pTail->next = pTmp;
    pTmp = new ListNode(8);
    pTail = pTail->next = pTmp;
    pTmp = new ListNode(2);
    pTail = pTail->next = pTmp;
    pTmp = new ListNode(9);
    pTail = pTail->next = pTmp;

    printList(pHead);

    ListNode *pRet = Solution().sortList(pHead);
    cout << "SUCCESS:";
    printList(pRet);

    freeList(pTail);

    return 0;
}
