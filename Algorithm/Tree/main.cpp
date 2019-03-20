#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <stack>
#include <queue> 

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void InsertLeft(TreeNode *pRoot, TreeNode *pLeft)
{
    pRoot->left = pLeft;
}

void InsertRight(TreeNode *pRoot, TreeNode *pRight)
{
    pRoot->right = pRight;
}

//二叉树先序遍历
void ProOrder(TreeNode *pRoot)
{
    if(NULL==pRoot)
    {
        return;
    }
    cout << pRoot->val << " ";
    ProOrder(pRoot->left);
    ProOrder(pRoot->right);
}


//二叉树中序遍历
void InOrder(TreeNode *pRoot)
{
    if(NULL==pRoot)
    {
        return;
    }
    InOrder(pRoot->left);
    cout << pRoot->val << " ";
    InOrder(pRoot->right);
}

//二叉树后序遍历
void PosOrder(TreeNode *pRoot)
{
    if(NULL==pRoot)
    {
        return;
    }
    PosOrder(pRoot->left);
    PosOrder(pRoot->right);
    cout << pRoot->val << " ";
}

void ProOrderUnRecur(TreeNode *pRoot)
{
    if(NULL == pRoot)
    {
        return;
    }
    cout << "树的先序遍历:";
    stack<TreeNode *> s;
    s.push(pRoot);
    while(!s.empty())
    {
        TreeNode *pTmp = s.top();
        s.pop();
        cout << pTmp->val << " ";
        if(NULL != pTmp->right)
        {
            s.push(pTmp->right);
        }
        if(NULL != pTmp->left)
        {
            s.push(pTmp->left);
        }
    }
    cout << endl;
}

void InOrderUnRecur(TreeNode *pRoot)
{
    if(NULL == pRoot)
    {
        return;
    }
    cout << "树的中序遍历:";
    stack<TreeNode *> s;
    TreeNode *pTmp = pRoot;
    while(NULL != pTmp)
    {
        s.push(pTmp);
        pTmp = pTmp->left;
    }
    while(!s.empty())
    {
        pTmp = s.top();
        s.pop();
        cout << pTmp->val << " ";
        pTmp = pTmp->right;
        while(NULL != pTmp)
        {
            s.push(pTmp);
            pTmp = pTmp->left;
        }
    }
    cout << endl;
}

//非递归二叉树的后续遍历
void PosOrderUnRecur1(TreeNode *pRoot)
{
    if(NULL == pRoot)
    {
        return;
    }
    cout << "树的后序遍历:";
    stack<TreeNode *> s1;
    stack<TreeNode *> s2;
    s1.push(pRoot);
    while(!s1.empty())
    {
        TreeNode *pTmp = s1.top();
        s1.pop();
        s2.push(pTmp);
        if(NULL != pTmp->left)
        {
            s1.push(pTmp->left);
        }
        if(NULL != pTmp->right)
        {
            s1.push(pTmp->right);
        }
    }
    while(!s2.empty())
    {
        cout << s2.top()->val << " ";
        s2.pop();
    }
    cout << endl;
}

void PosOrderUnRecur2(TreeNode *pRoot)
{
    if(NULL == pRoot)
    {
        return;
    }
    cout << "树的后序遍历:";
    stack<TreeNode *> s;
    s.push(pRoot);
    TreeNode *pLast;
    while(!s.empty())
    {
        TreeNode *pTmp = s.top();
        if((NULL==pTmp->left && NULL==pTmp->right)  //左子树为空 右子树为空
            || (pLast==pTmp->left && NULL==pTmp->right) //左子树已处理过 右子树为空
            || pLast==pTmp->right)     //右孩子已处理过
        {
            cout << pTmp->val << " ";
            s.pop();
            pLast = pTmp;
        }
        else
        {
            if(NULL != pTmp->right)
            {
                s.push(pTmp->right);
            }
            if(NULL != pTmp->left)
            {
                s.push(pTmp->left);
            }
        }
    }
    cout << endl;
}

void LevelOrder(TreeNode* pRoot)
{
    if(NULL == pRoot)
    {
        return;
    }
    cout << "树的层次遍历:";
    queue<TreeNode *> q;
    q.push(pRoot);
    while(!q.empty())
    {
        TreeNode *pTmp = q.front();
        q.pop();
        cout << pTmp->val << " ";
        if(NULL != pTmp->left)
        {
            q.push(pTmp->left);
        }
        if(NULL != pTmp->right)
        {
            q.push(pTmp->right);
        }
    }
    cout << endl;
}

bool FindNodeRecordPath(TreeNode* pRoot, TreeNode* pFind, vector<TreeNode*> &vecNode)
{
    if(NULL == pRoot || NULL == pFind)
    {
        return false;
    }
    if(pRoot == pFind)
    {
        vecNode.push_back(pRoot);
        return true;
    }
    if(FindNodeRecordPath(pRoot->left, pFind, vecNode))
    {
        vecNode.push_back(pRoot);
        return true;
    }
    if(FindNodeRecordPath(pRoot->right, pFind, vecNode))
    {
        vecNode.push_back(pRoot);
        return true;
    }
    return false;
}

void FindNodeRecordPath(TreeNode* pRoot, TreeNode* pFind)
{
    if(NULL==pRoot || NULL==pFind)
    {
        return;
    }
    cout << "寻找根节点到节点: " << pFind->val << " 的路径:  ";
    vector<TreeNode*> vecNode;
    if(FindNodeRecordPath(pRoot, pFind, vecNode))
    {
        for(vector<TreeNode*>::reverse_iterator it=vecNode.rbegin(); it!=vecNode.rend(); ++it)
        {
            cout << (*it)->val << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "未找到" << endl;
    }
}

int main()
{
    TreeNode *pTmp7 = new TreeNode(7);
    TreeNode *pTmp4 = new TreeNode(4);
    TreeNode *pTmp2 = new TreeNode(2);
    InsertLeft(pTmp2, pTmp7);
    InsertRight(pTmp2, pTmp4);

    TreeNode *pTmp6 = new TreeNode(6);
    TreeNode *pTmp5 = new TreeNode(5);
    InsertLeft(pTmp5, pTmp6);
    InsertRight(pTmp5, pTmp2);

    TreeNode *pTmp0 = new TreeNode(0);
    TreeNode *pTmp8 = new TreeNode(8);
    TreeNode *pTmp1 = new TreeNode(1);
    InsertLeft(pTmp1, pTmp0);
    InsertRight(pTmp1, pTmp8);

    TreeNode *pTmp3 = new TreeNode(3);
    InsertLeft(pTmp3, pTmp5);
    InsertRight(pTmp3, pTmp1);

    TreeNode *pRoot = pTmp3;
    cout << "树的先序遍历:";
    ProOrder(pRoot);
    cout << endl;
    ProOrderUnRecur(pRoot);
    cout << endl;

    cout << "树的中序遍历:";
    InOrder(pRoot);
    cout << endl;
    InOrderUnRecur(pRoot);
    cout << endl;

    cout << "树的后序遍历:";
    PosOrder(pRoot);
    cout << endl;
    PosOrderUnRecur1(pRoot);
    PosOrderUnRecur2(pRoot);
    cout << endl;

    LevelOrder(pRoot);
    cout << endl;

    FindNodeRecordPath(pRoot, pTmp6);
    FindNodeRecordPath(pRoot, pTmp4);
    FindNodeRecordPath(pRoot, pTmp0);
    cout << endl;

    delete pTmp0;
    delete pTmp1;
    delete pTmp2;
    delete pTmp3;
    delete pTmp4;
    delete pTmp5;
    delete pTmp6;
    delete pTmp7;
    delete pTmp8;

	return 0;
}
