#include <iostream>
#include <vector>
#include <algorithm>

namespace ClassicUsage{
    #define MAX 1000001
    std::vector<int> nums(MAX);
    std::vector<int> left(MAX);
    std::vector<int> right(MAX);
    std::vector<int> stack(MAX);
    int top = -1;

    void process(int n){
        top = -1;
        stack[++top] = -1;
        for(int i = 0;i < n;i++){
            while(stack[top] != -1 && nums[stack[top]] >= nums[i]){
                int cur = stack[top--];
                left[cur] = stack[top];
                right[cur] = i;
                
            }
            stack[++top] = i;
        }

        while(stack[top] != -1){
            int cur = stack[top--];
            left[cur] = stack[top];
            right[cur] = -1;
        }

        for(int i = n - 1;i >= 0;i--){
            if(right[i] != -1 && nums[right[i]] == nums[i]){
                right[i] = right[right[i]];
            }
        }
    }

    void input(){
        int n{};
        std::cin >> n;
        int num{};
        for(int i = 0;i < n;i++){
            std::cin >> nums[i];
        }
        process(n);
        for(int i = 0;i < n;i++){
            std::cout << left[i] << " " << right[i] << std::endl;
        }

        std::fill(nums.begin(), nums.end(), 0);
        std::fill(left.begin(), left.end(), 0);
        std::fill(right.begin(), right.end(), 0);
    }
}

namespace DailyTemperatures{
    class Solution {
    public:
    std::vector<int> dailyTemperatures(std::vector<int>& temperatures) {
        if(temperatures.empty())return {};
        std::vector<int> ans(temperatures.size());
        monotonousStack(ans, temperatures);
        return ans;
    }

    void monotonousStack(std::vector<int>& ans, std::vector<int>& tem){
        std::vector<int> stack(tem.size() + 1);
        int top = -1;
        stack[++top] = -1;
        for(int i = 0;i < tem.size();i++){
            while(stack[top] != -1 && tem[stack[top]] < tem[i]){
                ans[stack[top--]] = i;
            }

            stack[++top] = i;
        }

        while(stack[top] != -1){
            ans[stack[top--]] = -1;
        }

        // for(int i = ans.size() - 1;i >= 0;i--){
        //     if(ans[i] != -1 && tem[ans[i]] == tem[i]){
        //         ans[i] = ans[ans[i]];
        //     }
        // }

        for(int i = 0;i < ans.size();i++){
            if(ans[i] == -1){
                ans[i] = 0;
            }else{
                ans[i] = ans[i] - i;
            }
        }
    }
    };
}

namespace SumOfSubarrayMinimums{
#define MOD 1000000007
#define MAX 30001

class Solution {
public:
    int sumSubarrayMins(std::vector<int>& arr) {
        std::vector<int> stack(MAX, 0);
        int top = -1;
        stack[++top] = -1;
        int start{}, len{};
        int cur{};
        int ans{};
        for (int i = 0; i < arr.size(); i++) {
            while (stack[top] != -1 && arr[i] <= arr[stack[top]]) {
                cur = stack[top--];
                start = cur - stack[top];
                len = i - cur;
                ans = (ans % MOD + (static_cast<long long>(start) * len) % MOD * arr[cur]) % MOD;
            }

            stack[++top] = i;
        }

        while (stack[top] != -1) {
            cur = stack[top--];
            start = cur - stack[top];
            len = arr.size() - cur;
            ans = (ans % MOD + (static_cast<long long>(start) * len) % MOD * arr[cur]) % MOD;
        }

        return ans;
    }
};
}

namespace LargestRectangleInHistogram{
class Solution {
public:
    int largestRectangleArea(std::vector<int>& heights) {
        std::vector<int> stack(heights.size() + 1, 0);
        int top = -1;
        stack[++top] = -1;
        int ans{};
        int cur{};
        int len{};
        for(int i = 0;i < heights.size();i++){
            while(stack[top] != -1 && heights[stack[top]] >= heights[i]){
                cur = stack[top--];
                len = i - stack[top] - 1;
                ans = std::max(ans, heights[cur] * len);
            }

            stack[++top] = i;
        }

        while(stack[top] != -1){
            cur = stack[top--];
            len = heights.size() - stack[top] - 1;
            ans = std::max(ans, heights[cur] * len);
        }

        return ans;
    }
};
}

namespace MaximalRectangle{
class Solution {
public:
    std::vector<int> stack;
    int maximalRectangle(std::vector<std::vector<char>>& matrix) {
        if(matrix.empty())return 0;
        int row = static_cast<int>(matrix.size());
        int col = static_cast<int>(matrix[0].size());
        stack.resize(col + 1, 0);
        int ans{};
        std::vector<int> arr(col, 0);
        for(int i = 0;i < row;i++){
            for(int j = 0;j < col;j++){
                arr[j] = matrix[i][j] == '0' ? 0 : arr[j] + 1;
            }

            ans = std::max(ans, getMax(arr));
        }

        return ans;
    }

    int getMax(std::vector<int>& arr){
        int top = -1;
        stack[++top] = -1;
        int cur{}, ans{};
        for(int i = 0;i < arr.size();i++){
            while(stack[top] != -1 && arr[stack[top]] >= arr[i]){
                cur = stack[top--];
                ans = std::max(ans, (i - stack[top] - 1) * arr[cur]);
            }

            stack[++top] = i;
        }

        while(stack[top] != -1){
            cur = stack[top--];
            ans = std::max(ans, (static_cast<int>(arr.size()) - stack[top] - 1) * arr[cur]);
        }
        return ans;
    }
};
}

namespace MaximumWidthRamp{
class Solution {
public:
    int maxWidthRamp(std::vector<int>& nums) {
        std::vector<int> stack(nums.size(), 0);
        int top = -1;
        for(int i = 0;i < nums.size();i++){
            if(top == -1 || nums[stack[top]] > nums[i]){
                stack[++top] = i;
            }
        }
        int ans{};
        for(int i = nums.size() - 1;i >= 0;i--){
            while(top >= 0 && nums[stack[top]] <= nums[i]){
                ans = std::max(i - stack[top--], ans);
            }
        }

        return ans;
    }
};
}

namespace RemoveDuplicateLetters{
class Solution {
public:
    std::string removeDuplicateLetters(std::string s) {
        if(s.empty())return "";
        std::vector<int> map(26, 0);
        std::vector<bool> enter(26, false);
        for(auto& c : s){
            map[c - 'a']++;
        }

        std::vector<char> stack(s.size(), 0);
        int top{};
        for(int i = 0;i < s.size();i++){
            if(!enter[s[i] - 'a']){
                while(top > 0 && s[i] < stack[top - 1] && map[stack[top - 1] - 'a'] > 0){
                    enter[stack[top - 1] - 'a'] = false;
                    top--;
                }
                
                stack[top++] = s[i];
                enter[s[i] - 'a'] = true;
            }
            map[s[i] - 'a']--;
        }

        std::string ans(stack.begin(), stack.begin() + top);

        return ans;
    }
};
}

namespace FishEatFish{
    #define FMAX 100001
    std::vector<int> fishes(FMAX, 0);
    std::vector<int> fishStack(FMAX, 0);
    std::vector<int> roundStack(FMAX, 0);
    int top = 0;
    int compute(int N){
        if(N == 0)return 0;
        int ans{};
        for(int i = N - 1;i >= 0;i--){
            int newRound{};
            while(top > 0 && fishes[fishStack[top - 1]] < fishes[i]){
                newRound = std::max(roundStack[top - 1], newRound + 1);
                top--;
            }

            fishStack[top] = i;
            roundStack[top++] = newRound;
            ans = std::max(ans, newRound);
        }

        return ans;
    }

    void input(){
        int N{};
        std::cin >> N;
        for(int i = 0;i < N;i++){
            std::cin >> fishes[i];
        }

        std::cout << compute(N) << std::endl;
    }
}

namespace ShortestSubarrayWithSumAtLeastK{
class Solution {
public:
    int shortestSubarray(std::vector<int>& nums, int k) {
        std::vector<int> sums(nums.size() + 1, 0);
        std::vector<int> queue(nums.size() + 1, 0);
        int h{}, e{};
        for(int i = 1;i <= nums.size();i++){
            sums[i] = sums[i - 1] + nums[i - 1];
        }
        int ans = INT_MAX;
        for(int i = 0;i < sums.size();i++){
            while(h < e && sums[i] - sums[queue[h]] >= k){
                ans = std::min(ans, i - queue[h++]);
            }

            while(h < e && sums[queue[e - 1]] >= sums[i]){
                e--;
            }
            queue[e++] = i;
        }

        return ans == INT_MAX ? -1 : ans;
    }
};
}

namespace MaxValueOfEquation{
class Solution {
public:
    int findMaxValueOfEquation(std::vector<std::vector<int>>& points, int k) {
        std::vector<int> queue(points.size() + 1, 0);
        int h{}, e{};
        int ans = INT_MIN;
        for(int i = 0;i < points.size();i++){
            while(h < e && points[i][0] - points[queue[h]][0] > k){
                h++;
            }

            if(h < e){
                ans = std::max(ans, points[queue[h]][1] + points[i][1] + points[i][0] - points[queue[h]][0]);
            }

            while(h < e && points[queue[e - 1]][1] - points[queue[e - 1]][0] <= points[i][1] - points[i][0]){
                e--;
            }
            queue[e++] = i;
        }

        return ans;
    }
};
}

namespace MaximumNumberOfTasksYouCanAssign{
class Solution {
public:
    std::vector<int> queue;
    int maxTaskAssign(std::vector<int>& tasks, std::vector<int>& workers, int pills, int strength) {
        std::sort(tasks.begin(), tasks.end());
        std::sort(workers.begin(), workers.end());
        int tsize = static_cast<int>(tasks.size());
        int wsize = static_cast<int>(workers.size());
        queue.resize(std::max(tsize, wsize), 0);
        int ans{};
        for(int l = 0, r = std::min(tsize, wsize), m{};l <= r;){
            m = l + ((r - l) >> 1);
            if(f(tasks, workers, 0, m - 1, wsize - m, wsize - 1, strength, pills)){
                ans = m;
                l = m + 1;
            }else{
                r = m - 1;
            }
        }
        return ans;
    }

    bool f(std::vector<int>& tasks, std::vector<int>& workers, 
        int tl, int tr, int wl, int wr, int s, int pills){
            int cnt{};
            int h{}, e{};
            for(int i = tl, j = wl;j <= wr;j++){
                while(i <= tr && tasks[i] <= workers[j]){
                    queue[e++] = i++;
                }
                if(h < e && tasks[queue[h]] <= workers[j]){
                    h++;
                }else{
                    while(i <= tr && tasks[i] <= workers[j] + s){
                        queue[e++] = i++;
                    }

                    if(h < e){
                        cnt++;
                        e--;
                    }else{
                        return false;
                    }
                }
            }

            return cnt <= pills;
    }
};
}

int main(){
    std::vector<int> v = {1};
    ShortestSubarrayWithSumAtLeastK::Solution().shortestSubarray(v, 1);
}