#include <iostream>
#include <vector>
#include <algorithm>

namespace SortArrayByParity{
    class Solution {
    public:
        std::vector<int> sortArrayByParityII(std::vector<int>& nums) {
            int n = static_cast<int>(nums.size());

            int even = 0, odd = 1;
            while(odd < n && even < n){
                if((nums[n - 1] & 1) == 1){
                    swap(nums[n - 1], nums[odd]);
                    odd += 2;
                }else{
                    swap(nums[n - 1], nums[even]);
                    even += 2;
                }
            }

            return nums;
        }

        void swap(int& a, int& b){
            int temp = a;
            a = b;
            b = temp;
        }
    };
}

namespace FindTheDuplicateNumber{
    class Solution {
    public:
        int findDuplicate(std::vector<int>& nums) {
            if(nums.size() < 2){
                return -1;
            }
            int f = nums[nums[0]];
            int s = nums[0];
            while(f != s){
                f = nums[nums[f]];
                s = nums[s];
            }

            f = 0;
            while(f != s){
                f = nums[f];
                s = nums[s];
            }

            return f;
        }
    };
}

namespace TrappingRainWater{
    class Solution {
    public:
        int trap(std::vector<int>& height) {
            if(height.size() <= 2)return 0;
            int ans{};
            int l = 1, r = height.size() - 2, 
                lmax = height[0], rmax = height.back();
            while(l <= r){
                if(lmax <= rmax){
                    ans += std::max(0, lmax - height[l]);
                    lmax = std::max(lmax, height[l++]);
                }else{
                    ans += std::max(0, rmax - height[r]);
                    rmax = std::max(rmax, height[r--]);
                }
            }

            return ans;
        }
    };
}

namespace BoatsToSavePeople{
    class Solution {
    public:
        int numRescueBoats(std::vector<int>& people, int limit) {
            if(people.size() < 2)return people.size();
            std::sort(people.begin(), people.end());
            int l = 0, r = people.size() - 1;
            int sum{}, ans{};
            while(l <= r){
                sum = l == r ? people[l] : people[l] + people[r];
                if(sum > limit){
                    ans++;
                    r--;
                }else{
                    ans++;
                    l++;
                    r--;
                }
            }
            return ans;
        }
    };
}

namespace ContainerWithMostWater{
    class Solution {
    public:
        int maxArea(std::vector<int>& height) {
            if(height.size() < 2)return 0;
            int l{}, r = height.size() - 1;
            int ans{};
            while(l <= r){
                if(height[l] <= height[r]){
                    ans = std::max(ans, height[l] * (r - l));
                    l++;
                }else{
                    ans = std::max(ans, height[r] * (r - l));
                    r--;
                }
            }

            return ans;
        }
    };
}

namespace Heaters{
    class Solution {
    public:
        int findRadius(std::vector<int>& houses, std::vector<int>& heaters) {
            std::sort(houses.begin(), houses.end());
            std::sort(heaters.begin(), heaters.end());
            int ans{};
            for(int i = 0, j = 0;i < houses.size();i++){
                while(!best(i, j, houses, heaters)){
                    j++;
                }
                ans = std::max(ans, std::abs(houses[i] - heaters[j]));
            }

            return ans;
        }

        bool best(int i, int j, std::vector<int>& houses, std::vector<int>& heaters){
            return j == heaters.size() - 1
                || 
                std::abs(houses[i] - heaters[j]) < std::abs(houses[i] - heaters[j + 1]);
        }
    };
}

namespace FirstMissingPositive{
    class Solution {
    public:
        int firstMissingPositive(std::vector<int>& nums) {
            
            int l{}, r = nums.size();
            while(l < r){
                if(nums[l] == l + 1){
                    l++;
                }else if(nums[l] < l + 1 || nums[l] > r || nums[nums[l] - 1] == nums[l]){
                    swap(nums, l, --r);
                }else{
                    swap(nums, l, nums[l] - 1);
                }
            }

            return l + 1;
        }

        void swap(std::vector<int>& nums, int a, int b){
            int temp = nums[a];
            nums[a] = nums[b];
            nums[b] = temp;
        }
    };
}

int main(){
    std::vector<int> n = {2};
    FirstMissingPositive::Solution().firstMissingPositive(n);
}