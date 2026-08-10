#include <iostream>
#include <vector>
#include <climits>
#include <cmath>

namespace KillMonster{
    #define MAX 11
    std::vector<int> skills(MAX, 0);
    std::vector<int> bloods(MAX, 0);

    void swap(int i, int j){
        int temp = skills[i];
        skills[i] = skills[j];
        skills[j] = temp;
        temp = bloods[i];
        bloods[i] = bloods[j];
        bloods[j] = temp;
    }

    int process(int n, int i, int r){
        if(r <= 0)return i;
        if(i == n)return INT_MAX;

        int ans = INT_MAX;
        for(int j = i;j < n;j++){
            swap(i, j);
            ans = std::min(process(n, i + 1, r - (r <= bloods[i] ? 2 * skills[i] : skills[i])), ans);
            swap(i, j);
        }

        return ans;
    }

    int killMonster(int skillsNum, int monsterBlood){
        int ans = process(skillsNum, 0, monsterBlood);
        return ans == INT_MAX ? -1 : ans;
    }

    void input(){
        int T{};
        std::cin >> T;
        int n{}, m{};
        while(T-- > 0){
            std::cin >> n >> m;
            for(int i = 0;i < n;i++){
                std::cin >> skills[i] >> bloods[i];
            }
            std::cout << killMonster(n, m) << std::endl;
        }
    }
}

namespace Palindrome{
    class Solution {
    public:
        int superpalindromesInRange(std::string left, std::string right) {
            long long l = std::stoll(left);
            long long r = std::stoll(right);

            long long limit = static_cast<long long>(std::sqrt(r));
            long long seed = 1;
            long long num{};
            long long ans{};
            do{
                num = evenEnlarge(seed);
                if(num <= limit && check(num * num, l, r)){
                    ans++;
                }
                num = oddEnlarge(seed);
                if(num <= limit && check(num * num, l, r)){
                    ans++;
                }
                seed++;
            }while(num <= limit);
            return ans;
        }

        long long evenEnlarge(long long seed){
            long long ans = seed;
            while(seed > 0){
                ans = ans * 10 + seed % 10;
                seed /= 10;
            }
            return ans;
        }

        long long oddEnlarge(long long seed){
            long long ans = seed;
            seed /= 10;
            while(seed > 0){
                ans = ans * 10 + seed % 10;
                seed /= 10;
            }
            return ans;
        }
        
        bool check(long long n, long long l, long long r){
            return n >= l && n <= r && isPalindrome(n);
        }

        bool isPalindrome(long long x) {
            if(x < 0)return false;
            if(x < 10)return true;
            long long offset = 1;

            while(x / offset >= 10){
                offset *= 10;
            }

            while(offset > 1){
                if(x / offset != x % 10){
                    return false;
                }

                x = (x % offset) / 10;
                offset /= 100;
            }

            return true;
        }
    };
}

int main(){
    // KillMonster::input();
}