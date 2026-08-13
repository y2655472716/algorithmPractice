#include <iostream>
#include <vector>
#include <unordered_map>
namespace NumArray
{
    class NumArray
    {
    public:
        std::vector<int> sums;
        NumArray(std::vector<int> &nums)
        {
            sums.resize(nums.size() + 1);
            for (int i = 1; i < sums.size(); i++)
            {
                sums[i] = nums[i - 1] + sums[i - 1];
            }
        }

        int sumRange(int left, int right)
        {
            return sums[right + 1] - sums[left];
        }
    };
}

namespace LongestSubArray
{
#define MAX 100001
    std::vector<int> nums(MAX);
    int getAnswer(const int n, int aim)
    {
        int sum{};
        int ans{};
        std::unordered_map<int, int> sums;
        sums[0] = -1;
        for (int i = 0; i < n; i++)
        {
            sum += nums[i];
            if (sums.find(sum - aim) != sums.end())
            {
                ans = std::max(ans, i - sums[sum - aim]);
            }
            if (sums.find(sum) == sums.end())
            {
                sums[sum] = i;
            }
        }

        return ans;
    }

    void input()
    {
        int N{}, k{};
        std::cin >> N >> k;
        for (int i = 0; i < N; i++)
        {
            std::cin >> nums[i];
        }

        std::cout << getAnswer(N, k) << std::endl;
    }
}

namespace SubarraySum
{
    class Solution
    {
    public:
        int subarraySum(std::vector<int> &nums, int k)
        {
            int sum{};
            int ans{};
            std::unordered_map<int, int> sums;
            sums[0] = 1;
            for (int i = 0; i < nums.size(); i++)
            {
                sum += nums[i];
                if (sums.find(sum - k) != sums.end())
                {
                    ans += sums[sum - k];
                    sums[sum] = sums[sum] + 1;
                }
                else
                {
                    sums[sum] += 1;
                }
            }

            return ans;
        }
    };
}

namespace LongestBalancedSubArray
{
#define MAX 100001
    std::vector<int> nums(MAX);
    int longestBalancedSubArray(int n)
    {
        int ans{};
        std::unordered_map<int, int> sums;
        sums[0] = -1;
        int sum{};
        for (int i = 0; i < n; i++)
        {
            sum += nums[i] > 0 ? 1 : nums[i] == 0 ? 0
                                                  : -1;
            if (sums.find(sum) != sums.end())
            {
                ans = std::max(ans, i - sums[sum]);
            }

            if (sums.find(sum) == sums.end())
            {
                sums[sum] = i;
            }
        }

        return ans;
    }

    void input()
    {
        int N{};
        std::cin >> N;
        for (int i = 0; i < N; i++)
        {
            std::cin >> nums[i];
        }

        std::cout << longestBalancedSubArray(N) << std::endl;
    }
}

namespace LongestWPI
{
    class Solution
    {
    public:
        int longestWPI(std::vector<int> &hours)
        {
            int ans{};
            std::unordered_map<int, int> sums;
            int sum{};
            sums[0] = -1;
            for (int i = 0; i < hours.size(); i++)
            {
                sum += hours[i] > 8 ? 1 : -1;
                if (sum > 0)
                {
                    ans = i + 1;
                }
                else if (sums.find(sum - 1) != sums.end())
                {
                    ans = std::max(ans, i - sums[sum - 1]);
                }

                if (sums.find(sum) == sums.end())
                {
                    sums[sum] = i;
                }
            }

            return ans;
        }
    };
}

namespace MinSubarray
{
    class Solution
    {
    public:
        int minSubarray(std::vector<int> &nums, int p)
        {
            int all{};
            for (auto num : nums)
            {
                all %= p;
                all += num % p;
            }
            int mod = all % p;
            if (mod == 0)
                return 0;
            std::unordered_map<int, int> sums;
            sums[0] = -1;
            int sum{};
            int ans = nums.size();
            for (int i = 0; i < nums.size(); i++)
            {
                sum %= p;
                sum += nums[i] % p;
                int target = (sum % p + (p - mod) % p) % p;
                if (sums.find(target) != sums.end())
                {
                    ans = std::min(ans, i - sums[target]);
                }

                sums[sum % p] = i;
            }

            return ans == nums.size() ? -1 : ans;
        }
    };
}

namespace FindTheLongestSubstring{
    class Solution {
    public:
        int vowel(const char& c){
            switch(c){
                case 'a':return 0;
                case 'e':return 1;
                case 'i':return 2;
                case 'o':return 3;
                case 'u':return 4;
                default:return -1;
            }
        }
        int findTheLongestSubstring(std::string s) {
            int ans{};
            int map[32];
            std::fill(map, map + 32, -2);
            map[0] = -1;
            for(int i = 0, status = 0;i < s.size();i++){
                int vo = vowel(s[i]);
                if(vo != -1){
                    status ^= (1 << vo);
                }
                if(map[status] != -2){
                    ans = std::max(ans, i - map[status]);
                }else{
                    map[status] = i;
                }
            }
            return ans;
        }
    };
}

int main()
{
    FindTheLongestSubstring::Solution s;
    s.findTheLongestSubstring("abadad");
}