#include <iostream>
#include <vector>

namespace MinimumCostForTickets
{
    class Solution
    {
    public:
        int mincostTickets(std::vector<int> &days, std::vector<int> &costs)
        {
            std::vector<int> costDay = {1, 7, 30};
            int n = static_cast<int>(days.size());
            std::vector<int> dp(n + 1, INT_MAX);
            dp[n] = 0;
            for (int i = n - 1; i >= 0; i--)
            {
                for (int j = i, k = 0; k < 3; k++)
                {
                    while (j < n && days[i] + costDay[k] > days[j])
                    {
                        j++;
                    }

                    dp[i] = std::min(dp[i], costs[k] + dp[j]);
                }
            }

            return dp[0];
        }
    };
}

namespace DecodeWays
{
    class Solution
    {
    public:
        int numDecodings(std::string s)
        {
            return f2(s);
        }

        int f1(std::string &s, int i)
        {
            if (i == s.size())
                return 1;
            if (s[i] == '0')
                return 0;
            int p1{};
            int p2{};

            p1 = f1(s, i + 1);
            if (i + 1 < s.size() && ((s[i] == '1') || (s[i] == '2' && s[i + 1] <= '6')))
            {
                p2 = f1(s, i + 2);
            }

            return p1 + p2;
        }

        int f2(std::string &s)
        {
            int n = static_cast<int>(s.size());
            int lastLast = 0;
            int last = 1;
            for (int i = n - 1, cur{}; i >= 0; i--)
            {
                if (s[i] == '0')
                {
                    cur = 0;
                }
                else
                {
                    cur = last;
                    if (i + 1 < n && (s[i] == '1' || (s[i] == '2' && s[i + 1] <= '6')))
                    {
                        cur += lastLast;
                    }
                }
                lastLast = last;
                last = cur;
            }

            return last;
        }
    };
}

namespace DecodeWaysII
{
    class Solution
    {
    public:
        const int MOD = 1000000007;
        int numDecodings(std::string s)
        {
            return f2(s);
        }

        int f1(std::string &s, int i)
        {
            if (i == s.size())
                return 1;
            if (s[i] == '0')
                return 0;

            long long p1{}, p2{};
            if (s[i] != '*')
            {
                p1 += f1(s, i + 1) % MOD;
                if (i + 1 < s.size())
                {
                    if ((s[i] == '1' || (s[i] == '2' && s[i + 1] <= '6')) && s[i + 1] != '*')
                    {
                        p2 += f1(s, i + 2) % MOD;
                    }
                    else if (s[i] == '1' && s[i + 1] == '*')
                    {
                        p2 += ((f1(s, i + 2) % MOD) * 9LL) % MOD;
                    }
                    else if (s[i] == '2' && s[i + 1] == '*')
                    {
                        p2 += ((f1(s, i + 2) % MOD) * 6LL) % MOD;
                    }
                }
            }
            else
            {
                p1 += (9LL * (f1(s, i + 1) % MOD)) % MOD;
                if (i + 1 < s.size())
                {
                    if (s[i + 1] != '*')
                    {
                        if (s[i + 1] >= '0' && s[i + 1] <= '6')
                        {
                            p2 += (2LL * (f1(s, i + 2) % MOD)) % MOD;
                        }
                        else
                        {
                            p2 += f1(s, i + 2) % MOD;
                        }
                    }
                    else
                    {
                        long long p = f1(s, i + 2);
                        p2 += ((9LL * p) % MOD + (6LL * p) % MOD) % MOD;
                    }
                }
            }

            return static_cast<int>((p1 + p2) % MOD);
        }

        int f2(std::string &s)
        {
            int n = static_cast<int>(s.size());
            std::vector<long long> dp(n + 1);
            dp[n] = 1;
            for (int i = n - 1; i >= 0; i--)
            {
                if (s[i] == '0')
                {
                    dp[i] = 0;
                }
                else
                {
                    long long p1{}, p2{};
                    if (s[i] != '*')
                    {
                        p1 += dp[i + 1] % MOD;
                        if (i + 1 < n)
                        {
                            if ((s[i] == '1' || (s[i] == '2' && s[i + 1] <= '6')) && s[i + 1] != '*')
                            {
                                p2 += dp[i + 2] % MOD;
                            }
                            else if (s[i] == '1' && s[i + 1] == '*')
                            {
                                p2 += ((dp[i + 2] % MOD) * 9LL) % MOD;
                            }
                            else if (s[i] == '2' && s[i + 1] == '*')
                            {
                                p2 += ((dp[i + 2] % MOD) * 6LL) % MOD;
                            }
                        }
                    }
                    else
                    {
                        p1 += (9LL * dp[i + 1]) % MOD;
                        if (i + 1 < s.size())
                        {
                            if (s[i + 1] != '*')
                            {
                                if (s[i + 1] >= '0' && s[i + 1] <= '6')
                                {
                                    p2 += (2LL * (dp[i + 2] % MOD)) % MOD;
                                }
                                else
                                {
                                    p2 += dp[i + 2] % MOD;
                                }
                            }
                            else
                            {
                                p2 += ((9LL * dp[i + 2]) % MOD + (6LL * dp[i + 2]) % MOD) % MOD;
                            }
                        }
                    }
                    dp[i] = p1 + p2;
                }
            }

            return static_cast<int>(dp[0] % MOD);
        }
    };
}

int main()
{
    DecodeWays::Solution().numDecodings("12");
}