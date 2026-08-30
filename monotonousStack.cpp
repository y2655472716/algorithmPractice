#include <iostream>
#include <vector>

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

int main(){
    std::vector<int> v = {3,1,2,4};
    SumOfSubarrayMinimums::Solution().sumSubarrayMins(v);
}