#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

/*
   给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。
   你可以假设每种输入只会对应一个答案。但是，你不能重复利用这个数组中同样的元素。
   示例:
   给定 nums = [2, 7, 11, 15], target = 9
   因为 nums[0] + nums[1] = 2 + 7 = 9
   所以返回 [0, 1]
*/


class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        if(nums.size() < 2)
        {
            return vector<int>();
        }
        unordered_map<int, int> hMap;
        for(int n=0; n<nums.size(); ++n)
        {
            auto it = hMap.find(target - nums[n]);
            if(it != hMap.end())
            {
                return vector<int>{n, it->second};
            }
            hMap[nums[n]] = n;
        }

        return vector<int>();
#if 0
        vector<int> vRet;
        if(nums.size() < 2)
        {
            return vRet;
        }
        //数组不一定有序, 排序
        vector<int> vInt = nums;
        sort(vInt.begin(), vInt.end());
        
        unsigned i=0, j=vInt.size()-1;
        for(;i<j;)
        {
            int iTmp = vInt[i] + vInt[j];
            if(iTmp == target)
            {
                break;
            }
            else if(iTmp < target)
            {
                ++i;
            }
            else
            {
                --j;
            }
        }
        if(i<j)
        {
            int l=-1, r=-1;
            for(int k=0; k<nums.size(); ++k)
            {
                if(nums[k] == vInt[i])
                {
                    l = k;
                    break;
                }
            }
            for(int k=0; k<nums.size(); ++k)
            {
                if(nums[k] == vInt[j] && l!=k)
                {
                    r = k;
                    break;
                }
            }
            if(l!=-1 && r!=-1)
            {
                vRet.push_back(l);
                vRet.push_back(r);
            }
        }

        return vRet;
#endif
    }
};

int main()
{
    vector<int> nums{2, 7, 11, 15};
    int target = 9;
    vector<int> twoSum(Solution().twoSum(nums, target));
    for(int it : twoSum)
    {
        cout << it << " ";
    }
    cout << endl;
    return 0;
}
