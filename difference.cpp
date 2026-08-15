#include <iostream>
#include <vector>
#include <climits>
namespace CorpFlightBookings{
    class Solution {
    public:
        std::vector<int> corpFlightBookings(std::vector<std::vector<int>>& bookings, int n) {
            std::vector<int> cnt(n + 2, 0);
            for(auto& booking : bookings){
                cnt[booking[0]] += booking[2];
                cnt[booking[1] + 1] -= booking[2];
            }

            for(int i = 1;i < cnt.size();i++){
                cnt[i] += cnt[i - 1];
            }
            
            std::vector<int> ans(n);
            for(int i = 0;i < n;i++){
                ans[i] = cnt[i + 1];
            }

            return ans;
        }
    };
}

namespace ThreeStepKill{
    typedef long long LONG;
    #define T_MAX 10000003
    std::vector<long long> pillars(T_MAX, 0);
    struct Info{
      LONG _max{};
      LONG _xor{};  
    };

    void set(int l, int r, int s, int e){
        if(l == r){
        pillars[l] += s;
        return;
        }
        int d = (e - s) / (r - l);
        pillars[l] += s;
        pillars[l + 1] += d - s;
        pillars[r + 1] -= e + d;
        pillars[r + 2] += e;
    }

    void build(int n){
        for(int i = 1;i <= n;i++){
            pillars[i] += pillars[i - 1];
        }
        for(int i = 1;i <= n;i++){
            pillars[i] += pillars[i - 1];
        }
    }

    Info threeSetpKill(int n){
        Info ans{};
        LONG max = LLONG_MIN, Xor{};
        build(n);
        for(int i = 0;i <= n;i++){
            max = std::max(max, pillars[i]);
            Xor ^= pillars[i];
        }

        ans._max = max;
        ans._xor = Xor;
        return ans;
    }

    void input(){
        int n{}, m{};
        std::cin >> n >> m;
        int l{}, r{}, s{}, e{};
        while(m-- > 0){
            std::cin >> l >> r >> s >> e;
            set(l, r, s, e);
        }

        Info ans = threeSetpKill(n);
        std::cout << ans._xor << " " << ans._max << std::endl;
    }
}

namespace Lycanthropy{
    #define L_MAX 1000001
    #define OFFSET 30001
    typedef int LIN;
    std::vector<LIN> water(OFFSET + L_MAX + OFFSET, 0);

    void set(int l, int r, int s, int e, int d){
        water[l + OFFSET] += s;
        water[l + 1 + OFFSET] += d - s;
        water[r + 1 + OFFSET] -= d + e;
        water[r + 2 + OFFSET] += e;
    }

    void fall(int v, int x){
        set(x - v * 2, x, v, -v, -1);
        set(x - 3 * v + 1, x - v * 2 - 1, 1, v - 1, 1);
        set(x + 1, x + 2 * v, -v + 1, v, 1);
        set(x + 2 * v + 1, x + 3 * v - 1, v - 1, 1, -1);
    }

    void build(int m){
        for(int i = 1;i <= m + OFFSET;i++){
            water[i] += water[i - 1];
        }

        for(int i = 1;i <= m + OFFSET;i++){
            water[i] += water[i - 1];
        }
    }

    void input(){
        int n{}, m{};
        std::cin >> n >> m;
        int v{}, x{};
        while(n-- > 0){
            std::cin >> v >> x;
            fall(v, x);
        }

        build(m);

        std::cout << water[1 + OFFSET];
        for(int i = 2;i <= m;i++){
            std::cout << " " << water[i + OFFSET];
        }

        std::cout << std::endl;
    }
}



int main(){
    Lycanthropy::input();
}