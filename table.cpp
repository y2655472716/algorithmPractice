#include <iostream>
#include <cmath>
#include <vector>
namespace AppleBag{

    // int compute(int rest){
    //     if(rest < 0)return INT_MAX;
    //     if(rest == 0)return 0;

    //     int p1 = compute(rest - 8);
    //     int p2 = compute(rest - 6);
    //     p1 += p1 == INT_MAX ? 0 : 1;
    //     p2 += p2 == INT_MAX ? 0 : 1;

    //     return std::min(p1, p2);
    // }

    // int bag(int n){
    //     if((n & 1) != 0)return -1;
    //     int ans = compute(n);
    //     return ans == INT_MAX ? -1 : ans;
    // }

    int bag(int apple){
        if((apple & 1) != 0)return -1;

        if(apple < 18){
            if(apple == 0)return 0;

            if(apple == 6 || apple == 8)return 1;

            if(apple == 12 || apple == 14 || apple == 16){
                return 2;
            }
        }

        return (apple - 18) / 8 + 3;
    }
}

namespace EatGrass{

    std::string eatGrass(int grass, std::string cur){
        auto enemy = cur == "A" ? "B" : "A";

        if(grass < 5){
            return (grass == 0 || grass == 2) ? enemy : cur;
        }

        for(int pick = 1;pick <= grass;pick <<= 2){
            if(eatGrass(grass - pick, enemy) == cur){
                return cur;
            }
        }

        return enemy;
    }

    std::string win(int grass){
        if(grass % 5 == 0 || grass % 5 == 2){
            return "B";
        }
        return "A";
    }
}

namespace Is2{
    bool is2(int n){
        return (n & (n - 1)) != 0;
    }
}

namespace Palindrome{

    bool isPalindrome(const std::vector<char>& path, int l, int r){
        while(l < r){
            if(path[l] != path[r])return false;
            l++;
            r--;
        }

        return true;
    }
    
    int process(std::vector<char>& path, int i){
        if(i == path.size()){
            int cnt{};
            for(int l = 0;l < path.size();l++){
                for(int r = l + 1;r < path.size();r++){
                    if(isPalindrome(path, l, r)){
                        cnt++;
                    }

                    if(cnt > 1)return 0;
                }
            }

            return cnt == 1 ? 1 : 0;
        }else{
            int ans{};
            path[i] = 'r';
            ans += process(path, i + 1);
            path[i] = 'e';
            ans += process(path, i + 1);
            path[i] = 'd';
            ans += process(path, i + 1);
            return ans;
        }
    }

    int patchStr(int n){
        std::vector<char> path(n, 0);
        return process(path, 0);
    }

    int patchStr_simple(int n){
        if(n == 1)return 0;
        if(n == 2)return 3;
        if(n == 3)return 18;
        return 6 * (n + 1);
    }
}

int main(){
    for(int i = 1;i <= 10;i++){
        std::cout << i << ":" << Palindrome::patchStr_simple(i) << std::endl;
    }
}