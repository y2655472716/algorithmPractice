#include <iostream>
#include <vector>
#include <algorithm>

namespace KokoEatingBananas{
    class Solution {
    public:
        int minEatingSpeed(std::vector<int>& piles, int h) {
            if(piles.empty())return 0;
            int l = 1, r = 0;
            int ans{};
            for(auto& pile : piles){
                r = std::max(pile, r);
            }

            while(l <= r){
                int m = l + ((r - l) >> 1);
                if(f(piles, m) <= h){
                    ans = m;
                    r = m - 1;
                }else{
                    l = m + 1;
                }
            }
            return ans;
        }

        long long f(std::vector<int>& piles, int speed){
            long long sum{};
            for(auto& pile : piles){
                sum += (pile + speed - 1) / speed;
            }
            return sum;
        }
    };
}

namespace SplitArrayLargestSum{
    class Solution {
    public:
        int splitArray(std::vector<int>& nums, int k) {
            long long sum{};
            for(auto& num : nums){
                sum += num;
            }
            long long ans{};
            long long l = 0, r = sum;
            long long m{};
            while(l <= r){
                m = ((r - l) >> 1) + l;
                int need = f(nums, m);
                if(need <= k){
                    ans = need;
                    r = m - 1;
                }else{
                    l = m + 1;
                }
            }

            return static_cast<int>(ans);
        }

        int f(std::vector<int>& nums, long long limit){
            int part = 1;
            long long sum{};
            for(auto& num : nums){
                if(num > limit){
                    return INT_MAX;
                }
                if(sum + num > limit){
                    part++;
                    sum = num;
                }else{
                    sum += num;
                }
            }

            return part;
        }
    };
}

namespace RobotJump{
    #define MAX 100001
    std::vector<int> buildings(MAX, 0);

    bool canFinish(int E, int n, int max){
        for(int i = 0;i < n;i++){
            if(E <= buildings[i]){
                E -= buildings[i] - E;
            }else{
                E += E - buildings[i];
            }
            if(E >= max)return true;
            if(E < 0){
                return false;
            }
        }

        return true;
    }

    int robotJump(int n){
        int E{};
        int l{}, r{};
        int max{};
        for(int i = 0;i < n;i++){
            max = std::max(buildings[i], max);
        }
        r = max;
        int m{};
        while(l <= r){
            m = l + ((r - l) >> 1);
            if(canFinish(m, n, max)){
                E = m;
                r = m - 1;
            }else{
                l = m + 1;
            }
        }

        return E;
    }

    void input(){
        int N{};
        std::cin >> N;
        for(int i = 0;i < N;i++){
            std::cin >> buildings[i];
        }

        std::cout << robotJump(N) << std::endl;

    }
}

namespace FindKthSmallestPairDistance{
    class Solution {
    public:
        int smallestDistancePair(std::vector<int>& nums, int k) {
            std::sort(nums.begin(), nums.end());
            int l{}, r{};
            int ans{};
            for(auto& num : nums){
                r = std::max(r, num);
            }
            int m{};
            while(l <= r){
                m = l + ((r - l) >> 1);
                if(f(m, nums) >= k){
                    r = m - 1;
                    ans = m;
                }else{
                    l = m + 1;
                }
            }

            return ans;
        }

        int f(int m, std::vector<int>& nums){
            int ans{};
            for(int l = 0, r = 0;l < nums.size();l++){
                while(r + 1 < nums.size() && nums[r + 1] <= m + nums[l]){
                    r++;
                }
                ans += r - l;
            }

            return ans;  
        }
    };
}

namespace MaximumRunningTimeOfNComputers{
    class Solution {
    public:
        long long maxRunTime(int n, std::vector<int>& batteries) {
            int max{};
            long long sum{};
            for(auto& battery : batteries){
                sum += battery;
                max = std::max(max, battery);
            }
      
            if(sum >= static_cast<long long>(n) * max){
                return sum / static_cast<long long>(n);
            }
            int l{}, r = max;
            int m{};
            long long ans{};
            while(l <= r){
                m = l + ((r - l) >> 1);
                if(f(batteries, m, n)){
                    ans = static_cast<long long>(m);
                    l = m + 1;
                }else{
                    r = m - 1;
                }
            }

            return ans;
        }

        bool f(std::vector<int>& batteries, int m, int n){
            long long sum{};
            for(int i = 0;i < batteries.size();i++){
                if(batteries[i] >= m){
                    n--;
                }else{
                    sum += batteries[i];
                }
                if(sum >= static_cast<long long>(n) * m){
                    return true;
                }
            }

            return false;
        }
    };
}

namespace MinimumTimeYoCompleteTrips{
    class Solution {
    public:
        long long minimumTime(std::vector<int>& times, int totalTrips) {
            long long l{};
            long long r = INT_MAX;
            for(long long time : times){
                r = std::min(time, r);
            }
            l = r;
            r *= totalTrips;
            long long m{}, ans{};
            while(l <= r){
                m = l + ((r - l) >> 1);
                if(f(m, times) >= totalTrips){
                    ans = m;
                    r = m - 1;
                }else{
                    l = m + 1;
                }
            }

            return ans;
        }

        long long f(long long m, std::vector<int>& times){
            long long sum{};
            for(auto& time : times){
                sum += m / time;
            }

            return sum;
        }
    };
}

namespace KillMonster{

    bool f(int m, int hp, std::vector<int>& cuts, std::vector<int>& poisons){
        int n = std::min(static_cast<int>(cuts.size()), m);
        for(int i = 0, j = 1;i < n;i++, j++){
            hp -= std::max(cuts[i], (m - j) * poisons[i]);
            if(hp <= 0)return true;
        }

        return false;
    }

    int kill(std::vector<int>& cuts, std::vector<int>& poisons, int hp){
        int l{}, r{};
        r = hp + 1;
        int ans{}, m{};
        while(l <= r){
            m = l + ((r - l) >> 1);
            if(f(m, hp, cuts, poisons)){
                ans = m;
                r = m - 1;
            }else{
                l = m + 1;
            }
        }
        return ans;
    }
}

int main(){
}