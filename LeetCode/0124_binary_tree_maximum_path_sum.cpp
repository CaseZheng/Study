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
    void maxPathSum(TreeNode* root, int &iMaxPath, int &iMaxTruncated, int &iMaxSubTree)
    {
        if(NULL == root)
        {
            return;
        }
        int iLeftMaxPath=0, iLeftMaxSubTree=0, iLeftMaxTruncated=0, iRightMaxPath=0, iRightMaxSubTree=0, iRightMaxTruncated=0;
        maxPathSum(root->left, iLeftMaxPath, iLeftMaxTruncated, iLeftMaxSubTree);
        maxPathSum(root->right, iRightMaxPath, iRightMaxTruncated, iRightMaxSubTree);
        if(NULL==root->left && NULL==root->right)
        {
            iMaxPath = root->val;
            iMaxSubTree = root->val;
            iMaxTruncated = root->val;
        }
        else
        {
            int iLeftMax = iLeftMaxPath + root->val;
            int iRightMax = iRightMaxPath + root->val;
            iMaxPath = iLeftMax > iRightMax ? iLeftMax : iRightMax;
            iMaxPath = iMaxPath > root->val ? iMaxPath : root->val;

            if(NULL!=root->left && NULL==root->right)
            {
                iMaxTruncated = iLeftMaxTruncated > iLeftMax ? iLeftMaxTruncated : iLeftMax;
            }
            else if(NULL==root->left && NULL!=root->right)
            {
                iMaxTruncated = iRightMaxTruncated > iRightMax ? iRightMaxTruncated : iRightMax;
            }
            else
            {
                iMaxTruncated = iLeftMaxTruncated > iRightMaxTruncated ? iLeftMaxTruncated : iRightMaxTruncated;
                iMaxTruncated = iMaxTruncated > iMaxPath ? iMaxTruncated : iMaxPath;
            }
            iMaxTruncated = iMaxTruncated > root->val ? iMaxTruncated : root->val;
            
            int iCurTree = iLeftMaxPath + iRightMaxPath + root->val;
            if(NULL!=root->left && NULL==root->right)
            {
                iMaxSubTree = iLeftMaxSubTree > iCurTree ? iLeftMaxSubTree : iCurTree;
            }
            else if(NULL==root->left && NULL!=root->right)
            {
                iMaxSubTree = iRightMaxSubTree > iCurTree ? iRightMaxSubTree : iCurTree;
            }
            else
            {
                iMaxSubTree = iLeftMaxSubTree > iRightMaxSubTree ? iLeftMaxSubTree : iRightMaxSubTree;
                iMaxSubTree = iMaxSubTree > iCurTree ? iMaxSubTree : iCurTree;
            }
        }
    }
    int maxPathSum(TreeNode* root)
    {
        int iMaxPath=0;
        int iMaxSubTree=0;
        int iMaxTruncated=0;
        maxPathSum(root, iMaxPath, iMaxTruncated, iMaxSubTree);
        int iRet = iMaxSubTree > iMaxPath ? iMaxSubTree : iMaxPath;
        iRet = iMaxTruncated > iRet ? iMaxTruncated : iRet;
        return iRet;
    }
};



int main()
{
    //[-1,null,6,null,-4]           6
    //[-10,9,20,null,null,15,7]     42
    //[-10]                         -10
    return 0;
}
