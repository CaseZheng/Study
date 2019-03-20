#ifndef _PUBLIC_H_
#define _PUBLIC_H_

#include <iostream>
#include "unistd.h"

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

void freeList(ListNode *p)
{
	while(p != NULL)
	{
        ListNode* pTmp = p->next;
        free(p);
        p = pTmp;
	}
}

void printList(ListNode *p)
{
    while(p != NULL)
    {
        cout << p->val << " ";
        p = p->next;
    }
    cout << endl;

}

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


#endif
