#include <iostream>
#include <queue>
#include <unistd.h>

using namespace std;

/*
给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。
最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”
例如，给定如下二叉树:  root = [3,5,1,6,2,0,8,null,null,7,4]

                6
             ---------
            |         |    
            2         8
          -----       ---  
         |     |     |   |
         0     4     7   9
              ---
             |   |
             3   5

示例 1:
输入: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
输出: 3
解释: 节点 5 和节点 1 的最近公共祖先是节点 3。

示例 2:
输入: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
输出: 5
解释: 节点 5 和节点 4 的最近公共祖先是节点 5。因为根据定义最近公共祖先节点可以为节点本身。

说明:
    所有节点的值都是唯一的。
    p、q 为不同节点且均存在于给定的二叉树中。
*/

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

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

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        vector<TreeNode*> vP;
        if(!FindNodeRecordPath(root, p, vP))
        {
            return NULL;
        }
        vector<TreeNode*> vQ;
        if(!FindNodeRecordPath(root, q, vQ))
        {
            return NULL;
        }
        TreeNode *pTmp = NULL;
        TreeNode *pTmp1 = NULL;
        TreeNode *pTmp2 = NULL;
        while(pTmp1==pTmp2 && !vP.empty() && !vQ.empty())
        {
            pTmp1 = vP.back();
            vP.pop_back();
            pTmp2 = vQ.back();
            vQ.pop_back();
            pTmp = pTmp1==pTmp2 ? pTmp1 : pTmp;
        }
        return pTmp;
    }
};

int main()
{
    return 0;
}
