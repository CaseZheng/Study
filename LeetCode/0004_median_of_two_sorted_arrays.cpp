#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

/*
给定两个大小为 m 和 n 的有序数组 nums1 和 nums2。
请你找出这两个有序数组的中位数，并且要求算法的时间复杂度为 O(log(m + n))。
你可以假设 nums1 和 nums2 不会同时为空。

示例 1:
nums1 = [1, 3]
nums2 = [2]
则中位数是 2.0

示例 2:
nums1 = [1, 2]
nums2 = [3, 4]
则中位数是 (2 + 3)/2 = 2.5

*/

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if(nums1.empty() && nums2.empty())
        {
            return 0;
        }
        int sumSize = nums1.size() + nums2.size();
        int iIndex1 = -1;
        int iIndex2 = -1;
        if(sumSize%2 == 0)  //偶数个 需要找到中间的两个值
        {
            iIndex1 = sumSize/2-1;
            iIndex2 = sumSize/2;
        }
        else
        {
            iIndex1 = iIndex2 = sumSize/2;
        }
        int i=0;
        int j=0;
        int k=0;
        int num1=0;
        int num2=0;
        for(;i<nums1.size() || j<nums2.size(); ++k)
        {
            int num;
            if(i<nums1.size() && j<nums2.size() && nums1[i] <= nums2[j])
            {
                num = nums1[i++];
            }
            else if(i<nums1.size() && j<nums2.size() && nums1[i] > nums2[j])
            {
                num = nums2[j++];
            }
            else if(i<nums1.size())
            {
                num = nums1[i++];
            }
            else
            {
                num = nums2[j++];
            }
            if(k==iIndex1)
            {
                num1 = num;
                iIndex1 = -1;
            }
            if(k==iIndex2)
            {
                num2 = num;
                iIndex2 = -1;
            }
            if(-1==iIndex1 && -1==iIndex2)
            {
                break;
            }
        }
        return (double)(num1+num2)/2.0;
    }
};


int main()
{
    return 0;
}
