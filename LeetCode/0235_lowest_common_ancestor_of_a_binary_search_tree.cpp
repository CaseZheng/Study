#include <iostream>
#include <queue>
#include <unistd.h>

using namespace std;

/*
给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。
最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”
例如，给定如下二叉搜索树:  root = [6,2,8,0,4,7,9,null,null,3,5]

				6
			 ---------
			|         |	
		   2		  8
		 -----       ---  
		|     |     |   |
		0	  4     7   9
			 ---
			|   |
			3   5

示例 1:
输入: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
输出: 6 
解释: 节点 2 和节点 8 的最近公共祖先是 6。

示例 2:
输入: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
输出: 2
解释: 节点 2 和节点 4 的最近公共祖先是 2, 因为根据定义最近公共祖先节点可以为节点本身。
*/

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(NULL==p || NULL==q)
        {
            return NULL;
        }
        queue<TreeNode *> q1;
        queue<TreeNode *> q2;
        
        TreeNode *pTmp = root;
        while(pTmp!=p && NULL!=pTmp)
        {
            q1.push(pTmp);
            pTmp = (pTmp->val < p->val) ? pTmp->right : pTmp->left;     //小于被搜索节点 向右走
        }
        if(NULL == pTmp)
        {
            return NULL;
        }
        q1.push(pTmp);
        
        pTmp = root;
        while(pTmp!=q && NULL!=pTmp)
        {
            q2.push(pTmp);
            pTmp = (pTmp->val < q->val) ? pTmp->right : pTmp->left;     //小于被搜索节点 向右走
        }
        if(NULL == pTmp)
        {
            return NULL;
        }
        q2.push(pTmp);
        
        pTmp = NULL;
        while(!q1.empty() && !q2.empty() && q1.front() == q2.front())
        {
            pTmp = q1.front();
            q1.pop();
            q2.pop();
        }
        return pTmp;
    }
};

int main()
{
    return 0;
}
