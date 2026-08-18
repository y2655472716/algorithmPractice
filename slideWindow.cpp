#include <iostream>
#include <vector>
#include <climits>
#include <unordered_map>

namespace MinSubArrayLen{
    class Solution {
    public:
    int minSubArrayLen(int target, std::vector<int>& nums) {
        int ans = INT_MAX;
        int sum{};
        for(int l{}, r{};r < nums.size();r++){
            sum += nums[r];
            while(sum - nums[l] >= target){
                sum -= nums[l++];
            }
            if(sum >= target){
                ans = std::min(ans, r - l + 1);
            }
        }
        return ans == INT_MAX ? 0 : ans;
    }
    };  
}

namespace LongestSubstringWithoutRepeatingCharacters{
    class Solution {
    public:
        int lengthOfLongestSubstring(std::string s) {
            std::vector<int> map(256, -1);
            int ans{};
            for(int l = 0, r = 0;r < s.size();r++){
                l = std::max(map[s[r]] + 1, l);
                map[s[r]] = r;
                ans = std::max(ans, r - l + 1);
            }

            return ans;
        }
    };
}

namespace MinimumWindowSubstring{
    class Solution {
    public:
        std::string minWindow(std::string s, std::string t) {
            std::vector<int> map(256, 0);
            for(auto& c : t){
                map[c]--;
            }

            int debt = static_cast<int>(t.size());
            int len = INT_MAX;
            int start{};
            for(int l{}, r{};r < s.size();r++){
                if(map[s[r]]++ < 0){
                    debt--;
                }

                if(debt == 0){
                    while(map[s[l]] > 0){
                        map[s[l++]]--;
                    }

                    if(r - l + 1 < len){
                        len = r - l + 1;
                        start = l;
                    }
                }
            }

            return len == INT_MAX ? "" : s.substr(start, len);
        }
    };
}

namespace GasStation{
    class Solution {
    public:
        int canCompleteCircuit(std::vector<int>& gas, std::vector<int>& cost) {
            int n = static_cast<int>(gas.size());

            for(int l = 0, r = 0, sum;l < n;l = r + 1, r = l){
                sum = 0;
                while(sum + gas[r % n] - cost[r % n] >= 0){
                    if(r - l + 1 == n){
                        return l;
                    }

                    sum += gas[r % n] - cost[r % n];
                    r++;
                }
            }

            return -1; 
        }
    };
}

namespace ReplaceTheSubstringForBalancedString{
    class Solution {
    public:
        int balancedString(std::string s) {
            int n = static_cast<int>(s.size());
            std::unordered_map<int, int> map;
            for(auto& c : s){
                map[c]++;
            }
            int debt{};
            for(auto& pair : map){
                if(pair.second < n / 4){
                    pair.second = 0;
                }else{
                    pair.second = n / 4 - pair.second;
                    debt -= pair.second;
                }
            }
            if(debt == 0){
                return 0;
            }
            int ans = INT_MAX;

            for(int l{}, r{};r < s.size();r++){
                if(map[s[r]]++ < 0){
                    debt--;
                }

                if(debt == 0){
                    while(map[s[l]] > 0){
                        map[s[l++]]--;
                    }

                    ans = std::min(ans, r - l + 1);
                }
            }
            return ans;
        }
    };
}

namespace SubarraysWithKDifferentIntegers{
    class Solution {
    public:
        std::vector<int> map;

        int subarraysWithKDistinct(std::vector<int>& nums, int k) {
            
            return numsOfMostKinds(nums, k) - numsOfMostKinds(nums, k - 1);
        }

        int numsOfMostKinds(std::vector<int>& nums, int k){
            map.assign(20001, 0);
            int ans{};
            for(int l = 0, r = 0, collect = 0;r < nums.size();r++){
                if(++map[nums[r]] == 1)collect++;

                while(collect > k){
                    if(--map[nums[l++]] == 0){
                        collect--;
                    }
                }

                ans += r - l + 1;
            }
            return ans;
        }
    };
}

namespace LongestSubstringWithAtLeastKRepeatingCharacters{
    class Solution {
    public:
        int longestSubstring(std::string s, int k) {
            std::vector<int> map(26, 0);
            int ans{};
            for(int require = 1;require <= 26;require++){
                std::fill(map.begin(), map.end(), 0);

                for(int l{}, r{}, collect{}, satisfy{};r < s.size();r++){
                    map[s[r] - 'a']++;

                    if(map[s[r] - 'a'] == 1){
                        collect++;
                    }

                    if(map[s[r] - 'a'] == k){
                        satisfy++;
                    }

                    while(collect > require){
                        if(map[s[l] - 'a'] == k){
                            satisfy--;
                        }

                        if(map[s[l] - 'a'] == 1){
                            collect--;
                        }
                        map[s[l++] - 'a']--;
                    }

                    if(satisfy == require){
                        ans = std::max(ans, r - l + 1);
                    }
                }
            }

            return ans;
        }
    };
}

int main(){}