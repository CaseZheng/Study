#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

/*
给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。

示例 1:
输入: "abcabcbb"
输出: 3 
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。

示例 2:
输入: "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。

示例 3:
输入: "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。
*/

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
		int length = 0;
		for(int i=0; i<s.size(); ++i)
        {
            for(int j=i; j<s.size(); ++j)
            {
                if(find(s.begin()+i, s.begin()+j, s[j]) != s.begin()+j) //找到了
                {
                    length = (j-i) > length ? (j-i) : length;
                    break;
                }
                else
                {
                    length = (j-i+1) > length ? (j-i+1) : length;
                }
            }
        }
        return length;
    }
};

int main()
{

    Solution oSolution;
    string s;
    s = "abcabcbb";
    cout << "s:" << s << " " << oSolution.lengthOfLongestSubstring(s) << endl;
    s = "bbbbbbb";
    cout << "s:" << s << " " << oSolution.lengthOfLongestSubstring(s) << endl;
    s = "pwwkew";
    cout << "s:" << s << " " << oSolution.lengthOfLongestSubstring(s) << endl;
    s = "abcdefgfegeafefafafefaefefajojojojojo";
    cout << "s:" << s << " " << oSolution.lengthOfLongestSubstring(s) << endl;
    s = " ";
    cout << "s:" << s << " " << oSolution.lengthOfLongestSubstring(s) << endl;
    s = " a";
    cout << "s:" << s << " " << oSolution.lengthOfLongestSubstring(s) << endl;
    return 0;
}
