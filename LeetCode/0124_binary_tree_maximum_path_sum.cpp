#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "public.h"

using namespace std;

/*
给定一个非空二叉树，返回其最大路径和。
本题中，路径被定义为一条从树中任意节点出发，达到任意节点的序列。该路径至少包含一个节点，且不一定经过根节点。

示例 1:
输入: [1,2,3]
       1
      / \
     2   3
输出: 6
示例 2:

输入: [-10,9,20,null,null,15,7]
   -10
   / \
  9  20
    /  \
   15   7
输出: 42

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
*/

class Solution {
public:
    void maxPathSum(TreeNode* root, int &iMaxPath, int &iMaxSubTree)
    {
        if(NULL == root)
        {
            return;
        }
        int iLeftMaxPath=0, iLeftMaxSubTree=0, iRightMaxPath=0, iRightMaxSubTree=0;
        maxPathSum(root->left, iLeftMaxPath, iLeftMaxSubTree);
        maxPathSum(root->right, iRightMaxPath, iRightMaxSubTree);
        if(NULL==root->left && NULL==root->right)
        {
            iMaxPath = root->val;
            iMaxSubTree = root->val;
        }
        else
        {
            int iLeftMax = iLeftMaxPath + root->val;
            int iRightMax = iRightMaxPath + root->val;
            iMaxPath = iLeftMax > iRightMax ? iLeftMax : iRightMax;
            iMaxPath = iMaxPath > root->val ? iMaxPath : root->val;

            int iCurTree = iLeftMaxPath + iRightMaxPath + root->val;
            if(NULL!=root->left && NULL==root->right)
            {
                iMaxSubTree = iLeftMaxSubTree > iCurTree ? iLeftMaxSubTree : iCurTree;
                iMaxSubTree = iLeftMax > iMaxSubTree ? iLeftMax : iMaxSubTree;
            }
            else if(NULL==root->left && NULL!=root->right)
            {
                iMaxSubTree = iRightMaxSubTree > iCurTree ? iRightMaxSubTree : iCurTree;
                iMaxSubTree = iRightMax > iMaxSubTree ? iRightMax : iMaxSubTree;
            }
            else
            {
                iMaxSubTree = iLeftMaxSubTree > iRightMaxSubTree ? iLeftMaxSubTree : iRightMaxSubTree;
                iMaxSubTree = iMaxSubTree > iCurTree ? iMaxSubTree : iCurTree;
                iMaxSubTree = iLeftMax > iMaxSubTree ? iLeftMax : iMaxSubTree;
                iMaxSubTree = iRightMax > iMaxSubTree ? iRightMax : iMaxSubTree;
            }
            iMaxSubTree = iMaxSubTree > root->val ? iMaxSubTree : root->val;
        }
    }
    int maxPathSum(TreeNode* root)
    {
        int iMaxPath=0;
        int iMaxSubTree=0;
        maxPathSum(root, iMaxPath, iMaxSubTree);
        return iMaxPath > iMaxSubTree ? iMaxPath : iMaxSubTree;
    }
};

int main()
{
    //[-1,null,6,null,-4]                   6
    //[-10,9,20,null,null,15,7]             42
    //[-10]                                 -10
    //[-1,null,9,-6,3,null,null,null,-2]    12
    return 0;
}
