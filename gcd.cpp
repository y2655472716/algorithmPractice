#include <iostream>

namespace Gcd{
    int gcd(int a, int b){
        return b == 0 ? a : gcd(b, a % b);
    }

    int lcm(int a, int b){
        return a / gcd(a, b) * b;
    }
}

namespace NthMagicalNumber{

    int gcd(int a, int b){
        return b == 0 ? a : gcd(b, a % b);
    }

    int lcm(int a, int b){
        return a / gcd(a, b) * b;
    }
}

namespace NthMagicalNumber{

    long long gcd(long long a, long long b) {
        return b == 0 ? a : gcd(b, a % b);
    }

    long long lcm(long long a, long long b) { return a / gcd(a, b) * b; }

    int nthMagicalNumber(int n, long long a, long long b) {
        if (n == 0)
            return 0;
        long long _lcm = lcm(a, b);
        long long ans;

        for (long long l = 0, r = std::min(a, b) * (long long)n, m = 0; l <= r;) {
            m = l + (r - l) / 2;
            if (m / a + m / b - m / _lcm >= n) {
                ans = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }

        return static_cast<int>(ans % 1000000007);
    }
}

int main(){
    std::cout << Gcd::gcd(24, 16) << std::endl;
    std::cout << Gcd::lcm(24, 16) << std::endl;
}