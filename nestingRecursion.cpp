#include <iostream>
#include <stack>
#include <vector>
#include <map>
namespace Caculator{

    int compute(std::vector<int>& nums, std::vector<char>& ops){
        if(nums.empty()) return 0;
        int ans = nums[0];
        int n = nums.size();
        for(int i = 1;i < n;i++){
            ans += ops[i - 1] == '+' ? nums[i] : - nums[i];
        }
        return ans;
    }

    void push(int cur, char op, std::vector<int>& nums, std::vector<char>& ops){
        if(nums.empty()) return;
        int n = nums.size();
        if(nums.empty() || ops.empty() || ops.back() == '+' || ops.back() == '-'){
            nums.push_back(cur);
            ops.push_back(op);
        }else{
            int topNum = nums.back();
            char topOp = ops.back();
            if(topOp == '*'){
                nums.back() = topNum * cur;
            }else{
                nums.back() = topNum / cur;
            }

            ops.back() = op;
        }
    }

    int process(std::string& s, int& where){
        int cur{};
        std::vector<int> nums;
        std::vector<char> ops;

        while(where < s.size() && s[where] != ')'){
            if(s[where] >= '0' && s[where] <= '9'){
                cur = cur * 10 + (s[where++] - '0');
            }else if(s[where] != '('){
                push(cur, s[where++], nums, ops);
                cur = 0;
            }else{
                cur = process(s, ++where);
                where++;
            }
            
        }
        push(cur, '+', nums, ops);
        return compute(nums, ops);
    }

    int caculate(std::string& s){
        if(s.empty())return 0;
        int where = 0;
        return process(s, where);
    }
}

namespace DecodeString{

    std::string copy(int cnt, std::string s){
        std::string path;
        for(int i = 0;i < cnt;i++){
            path += s;
        }
        return path;
    }

    std::string decode(std::string& s, int& index){
        std::string ans{};
        int count{};
        while(index < s.size() && s[index] != ']'){
            if(s[index] >= '0' && s[index] <= '9'){
                count = count * 10 + (s[index++] - '0');
            }else if(s[index] != '['){
                ans += s[index++];
            }else{
                ans += copy(count, decode(s, ++index));
                index++;
                count = 0;
            }
        }
        return ans;
    }

    std::string decodeString(std::string s) {
        if(s.empty())return std::string();
        int index{};
        return decode(s, index);
    }
}

namespace CountOfAtoms{
    void fill(std::map<std::string, int>& ans, std::string& name, std::map<std::string, int>& pre, int cnt){
        if(!name.empty() || !pre.empty()){
            cnt = cnt == 0 ? 1 : cnt;
            if(!name.empty()){
                ans[name] += cnt;
            }else{
            for (const auto& [atom, num] : pre) {
                    ans[atom] += num * cnt;
                }
            }
        }
    }
    std::map<std::string, int> count(std::string& formula, int& index){
        std::map<std::string, int> ans;
        std::string name{};
        int cnt{};
        std::map<std::string, int> pre;
        while(index < formula.size() && formula[index] != ')'){
            if(formula[index] >= 'A' && formula[index] <= 'Z' || formula[index] == '('){
                fill(ans, name, pre, cnt);
                name.clear();
                cnt = 0;
                pre.clear();
                if(formula[index] >= 'A' && formula[index] <= 'Z'){
                    name += formula[index++];
                }else{
                    pre = count(formula, ++index);
                }
            }else if(formula[index] >= '0' && formula[index] <= '9'){
                cnt = cnt * 10 + (formula[index++] - '0');
            }else{
                name += formula[index++];
            }
        }
        fill(ans, name, pre, cnt);
        index++;
        return ans;
    }

    std::string countOfAtoms(std::string formula) {
        if(formula.empty())return {};
        int index{};
        std::map<std::string, int> atoms = count(formula, index);
        
        std::string ans;
        for(auto[atom, count] : atoms){
            ans += atom;
            if(count == 1)continue;
            ans += std::to_string(count);
        }
        return ans;
    }
}

int main(){
    std::string s = "K4(ON(SO3)2)2";
    std::cout << CountOfAtoms::countOfAtoms(s) << std::endl;
}