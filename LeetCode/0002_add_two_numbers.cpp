#include <iostream>
#include <stack>
#include <unistd.h>
#include "public.h"

using namespace std;

/*
给出两个 非空 的链表用来表示两个非负的整数。其中，它们各自的位数是按照 逆序 的方式存储的，并且它们的每个节点只能存储 一位 数字。
如果，我们将这两个数相加起来，则会返回一个新的链表来表示它们的和。
您可以假设除了数字 0 之外，这两个数都不会以 0 开头。
示例：
输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
输出：7 -> 0 -> 8
原因：342 + 465 = 807

struct ListNode {
	int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
*/


class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* lRet = NULL;
        ListNode* lTail = NULL;
        int iSum = 0;
        int iCarry = 0;
        while(l1 != NULL || l2 != NULL)
        {
            iSum = 0;
            if(l1!=NULL && l2!=NULL)
            {
                iSum = l1->val + l2->val;
            }
            else if(l1!=NULL)
            {
                iSum = l1->val;
            }
            else
            {
                iSum = l2->val;
            }
            iSum += iCarry;
            iCarry = 0;
            if(iSum >= 10)
            {
                iSum -= 10;
                iCarry += 1;
            }
            ListNode* pTmp = new ListNode(iSum);
            if(lRet == NULL)
            {
                lTail = lRet = pTmp;
            }
            else
            {
                lTail->next = pTmp;
                lTail = pTmp;
            }
            if(l1!=NULL) { l1=l1->next; }
            if(l2!=NULL) { l2=l2->next; }
        }
        if(iCarry != 0)
        {
            ListNode* pTmp = new ListNode(iCarry);
            lTail->next = pTmp;
        }
        
        return lRet;
    }
};


int main()
{
	ListNode* l1 = NULL;
	ListNode* pTmp = new ListNode(3);
	l1 = pTmp;
    pTmp = new ListNode(4);
    pTmp->next = l1;
    l1 = pTmp;
    pTmp = new ListNode(2);
    pTmp->next = l1;
    l1 = pTmp;

	ListNode* l2 = NULL;
	pTmp = new ListNode(4);
	l2 = pTmp;
    pTmp = new ListNode(6);
    pTmp->next = l2;
    l2 = pTmp;
    pTmp = new ListNode(5);
    pTmp->next = l2;
    l2 = pTmp;

    printList(l1);
    printList(l2);
	ListNode* lRet = Solution().addTwoNumbers(l1, l2);
    printList(lRet);

    freeList(l1);
    freeList(l2);
    freeList(lRet);
    return 0;
}
