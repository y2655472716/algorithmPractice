#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <stack>

namespace GeneratePermutation{

    void f(std::string s, int index, std::string& path, std::vector<std::string>& ans, std::unordered_set<std::string>& set){
        if(index == s.size()){
            if(set.find(path) == set.end()){
                ans.push_back(path);
                set.insert(path);
            }
        }else{
            path.push_back(s[index]);
            f(s, index + 1, path, ans, set);
            path.pop_back();
            f(s, index + 1, path, ans, set);
        }
    }

    std::vector<std::string> generatePermutation(std::string s) {
        if(s.empty())return {""};
        std::vector<std::string> ans;
        std::string path;
        std::unordered_set<std::string> set;
        f(s, 0, path, ans, set);
        return ans;
    }
}

namespace SubsetsWithDup{

    void f(std::vector<int>& nums, int i, std::vector<int>& path, std::vector<std::vector<int>>& ans){
        if(i == nums.size()){
            ans.push_back(path);
        }else{
            int j = i + 1;
            while(j < nums.size() && nums[i] == nums[j]){
                j++;
            }

            f(nums, j, path, ans);
            for(int k = i;k < j;k++){
                path.push_back(nums[i]);
                f(nums, j, path, ans);
            }
            for(;i < j;i++){
                path.pop_back();
            }
        }
    }

    std::vector<std::vector<int>> subsetsWithDup(std::vector<int>& nums) {
        if(nums.empty())return {};

        std::vector<int> path;
        std::vector<std::vector<int>> ans;
        std::sort(nums.begin(), nums.end());
        f(nums, 0, path,ans);
        return ans;
    }
}

namespace Permute{

    void swap(std::vector<int>& nums, int i, int j){
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    void process(std::vector<int>& nums, int i, std::vector<std::vector<int>>& ans){
        if(i == nums.size()){
            ans.push_back(nums);
        }else{
            std::unordered_set<int> set;
            for(int j = i;j < nums.size();j++){
                if(set.find(nums[j]) == set.end()){
                    set.insert(nums[j]);
                    swap(nums, i, j);
                    process(nums, i + 1, ans);
                    swap(nums, i, j);
                }

            }
        }
    }

    std::vector<std::vector<int>> permuteUnique(std::vector<int>& nums) {
        if(nums.empty())return {};
        std::vector<std::vector<int>> ans;
        process(nums, 0, ans);
        return ans;
    }
}

namespace Reverse{

    int bottomOut(std::stack<int>& stack){
        int ans = stack.top();
        stack.pop();
        if(stack.empty()){
            return ans;
        }

        int last = bottomOut(stack);
        stack.push(ans);
        return last;
    }

    void reverse(std::stack<int>& stack){
        if(stack.empty())return;

        int num = bottomOut(stack);
        reverse(stack);
        stack.push(num);
    }
}

namespace SortStack{

    int Deep(std::stack<int>& stack){
        if(stack.empty())return 0;

        int num = stack.top();
        stack.pop();
        int deep = Deep(stack);
        stack.push(num);
        return deep + 1;
    }

    int Max(std::stack<int>& stack, int deep){
        if(deep == 0){
            return INT_MIN;
        }

        int num = stack.top();
        stack.pop();
        int max = Max(stack, deep - 1);
        stack.push(num);
        return std::max(num, max);
    }

    int num(std::stack<int>& stack, int deep, int max){
        if(deep == 0){
            return 0;
        }

        int n = stack.top();
        stack.pop();
        int k = num(stack, deep - 1, max);
        stack.push(n);
        return n == max ? k + 1 : k;
    }

    void down(std::stack<int>& stack, int deep, int max, int k){
        if(k == 0)return;

        if(deep == 0){
            while(k > 0){
                stack.push(max);
                k--;
            }
            return;
        }

        int num = stack.top();
        stack.pop();
        down(stack, deep - 1, max, k);
        if(num != max)stack.push(num);
    }

    void sort(std::stack<int>& stack){
        if(stack.empty())return;
        int deep = Deep(stack);
        while(deep > 0){
            int max = Max(stack, deep);
            int k = num(stack, deep, max);
            down(stack, deep, max, k);
            deep -= k;
        }
    }
}

namespace Hanoi{

    void f(int n, std::string move, std::string medium, std::string to){
        if(n == 1){
            std::cout << n << "从" << move << "移动到" << to << std::endl;
        }else{
            f(n - 1, move, to, medium);
            std::cout << n << "从" << move << "移动到" << to << std::endl;
            f(n - 1, medium, move, to);
        }
    }

    void hanoi(int n){
        if(n > 0){
            f(n, "左", "中", "右");
        }
    }
}

int main(){
    
}