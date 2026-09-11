#include <iostream>
#include <vector>
#include <algorithm>

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

namespace UglyNumber{
class Solution {
public:
    int nthUglyNumber(int n) {
        std::vector<int> dp(n + 1, 0);
        dp[1] = 1;
        for(int i = 2, p2 = 1, p3 = 1, p5 = 1;i <= n;i++){
            int a = dp[p2] * 2;
            int b = dp[p3] * 3;
            int c = dp[p5] * 5;
            dp[i] = std::min({a, b, c});
            if(dp[i] == a)p2++;
            if(dp[i] == b)p3++;
            if(dp[i] == c)p5++;
        }

        return dp[n];
    }
};
}

namespace LongestValidParentheses{
class Solution {
public:
    int longestValidParentheses(std::string s) {
        int n = static_cast<int>(s.size());
        std::vector<int> dp(n + 1);
        int ans{};
        for(int i = 1;i < n;i++){
            if(s[i] == ')'){
                int p = i - dp[i - 1] - 1;
                if(p >= 0 && s[p] == '('){
                    dp[i] += dp[i - 1] + 2 + (p > 0 ? dp[p - 1] : 0);
                }
            }

            ans = std::max(ans, dp[i]);
        }

        return ans;
    }
};
}

namespace UniqueSubstringsInWraparoundString{
class Solution {
public:
    int findSubstringInWraproundString(std::string& s) {
        int n = static_cast<int>(s.size());
        std::vector<int> dp(26);
        dp[s[0] - 'a'] = 1;
        int len = 1;
        for(int i = 1, cur{}, pre{};i < n;i++){
            cur = static_cast<int>(s[i] - 'a');
            pre = static_cast<int>(s[i - 1] - 'a');

            if((pre + 1) % 26 == cur){
                len++;
            }else{
                len = 1;
            }

            dp[cur] = std::max(len, dp[cur]);
        }

        int ans{};
        for(int i = 0;i < 26;i++){
            ans += dp[i];
        }
        return ans;
    }
}; 
}

namespace DistinctSubsequences{
class Solution {
public:
    const int MOD = 1000000007;
    int distinctSubseqII(std::string& s) {
        std::vector<int> dp(26);
        int all = 1;
        for(int i = 0;i < s.size();i++){
            int c = s[i] - 'a';
            int ne = (all - dp[c] + MOD) % MOD;
            all = (all + ne) % MOD;
            dp[c] = (ne + dp[c]) % MOD;
        }

        return (all - 1 + MOD) % MOD;
    }
};
}

namespace MinimumPathSum{
class Solution {
public:
    int minPathSum(std::vector<std::vector<int>>& grid) {
        return f2(grid);
    }

    int f1(std::vector<std::vector<int>>& grid, int i, int j){
        int n = static_cast<int>(grid.size());
        int m = static_cast<int>(grid[0].size());
        if(i == n || j == m){
            return INT_MAX;
        }

        if(i == n - 1 && j == m - 1){
            return grid[i][j];
        }

        int p1{}, p2{};
        p1 = f1(grid, i + 1, j);
        p2 = f1(grid, i, j + 1);

        return std::min(p1, p2) + grid[i][j];
    }

    int f2(std::vector<std::vector<int>>& grid){
        int n = static_cast<int>(grid.size());
        int m = static_cast<int>(grid[0].size());
        std::vector<int> dp(m);

        dp[0] = grid[0][0];
        for(int i = 1;i < m;i++){
            dp[i] = dp[i - 1] + grid[0][i];
        }

        for(int i = 1;i < n;i++){
            dp[0] += grid[i][0];
            for(int j = 1;j < m;j++){
                dp[j] = std::min(dp[j - 1], dp[j]) + grid[i][j];
            }
        }

        return dp[m - 1];

    }
};
}

namespace WordSearch{
class Solution {
public:
    std::vector<int> move;
    bool exist(std::vector<std::vector<char>>& board, std::string word) {
        int s = static_cast<int>(word.size());
        int n = static_cast<int>(board.size());
        int m = static_cast<int>(board[0].size());
        move = {-1, 0, 1, 0, -1};
        for(int i = 0;i < n;i++){
            for(int j = 0;j < m;j++){
                if(board[i][j] == word[0]){
                    if(dfs(board, word, i, j, 1)){
                        return true;
                    }
                }
            }
        }

        return false;
    }

    bool dfs(std::vector<std::vector<char>>& board, std::string& word, int x, int y, int k){
        if(k == word.size())return true;
        char temp = board[x][y];
        board[x][y] = '#';
        for(int i = 0;i < 4;i++){

            int nx = x + move[i];
            int ny = y + move[i + 1];
            if(nx >= 0 && ny >= 0 && nx < board.size() && ny < board[0].size() && board[nx][ny] == word[k]){
                if(dfs(board, word, nx, ny, k + 1)){
                    board[x][y] = temp;
                    return true;
                }
            }
            
        }
        board[x][y] = temp;
        return false;
    }

    
};
}

namespace LongestCommonSubsequence{
class Solution {
public:
    int longestCommonSubsequence(std::string text1, std::string text2) {
        int s1 = static_cast<int>(text1.size());
        int s2 = static_cast<int>(text2.size());

        std::vector<std::vector<int>> dp(s1, std::vector<int>(s2, 0));
        for(int i = 0;i < s1;i++){
            if(text1[i] == text2[0]){
                dp[i][0] = 1;
            }else if(i > 0){
                dp[i][0] = dp[i - 1][0];
            }
        }
        for(int j = 1;j < s2;j++){
            if(text1[0] == text2[j]){
                dp[0][j] = 1;
            }else{
                dp[0][j] = dp[0][j - 1];
            }
        }

        for(int i = 1;i < s1;i++){
            for(int j = 1;j < s2;j++){
                if(text1[i] == text2[j]){
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }else{
                    dp[i][j] = std::max(dp[i][j - 1], dp[i - 1][j]);
                }
            }
        }

        return dp[s1 - 1][s2 - 1];
    }
};
}

namespace LongestPalindromicSubsequence{
class Solution {
public:
    int longestPalindromeSubseq(std::string s) {
        return f2(s);
    }

    int f1(std::string& s, int l, int r){
        if(l > r || r == s.size())return 0;
        if(l == r)return 1;
        
        int p1{}, p2{}, p3{};
        if(s[l] == s[r]){
            p1 = 2 + f1(s, l + 1, r - 1);
        }
        p2 = f1(s, l, r - 1);
        p3 = f1(s, l + 1, r);
        return std::max({p1, p2, p3});
    }

    int f2(std::string& s){
        int n = static_cast<int>(s.size());
        std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));
        
        for(int i = 0;i < n;i++){
            dp[i][i] = 1;
        }

        for(int l = n - 2;l >= 0;l--){
            for(int r = l + 1;r < n;r++){
                if(s[l] == s[r]){
                    dp[l][r] = 2 + dp[l + 1][r - 1];
                }
                dp[l][r] = std::max({dp[l][r], dp[l + 1][r], dp[l][r - 1]});
            }
        }

        return dp[0][n - 1];
    }
};
}

namespace BinaryTree{
    #define MOD 1000000007
    int n{}, h{};
    #define MAX 51
    std::vector<int> dp(MAX, 0);
    int f1(int node, int height){
        if(node < height)return f1(node, node);
        if(node == 0)return 1;
        if(node == (1 << height) - 1)return 1;
        if(node > (1 << height) - 1)return 0;
        if(node == 1)return 1;
        int ans{};
        for(int i = 0;i < node;i++){
            ans += (f1(i, height - 1) % MOD * f1(node - i - 1, height - 1) % MOD) % MOD;
        }

        return ans;
    }

    int f2(){
        dp[0] = 1;
        for(int i = 1;i <= h;i++){
            for(int j = n;j >= 1;j--){
                dp[j] = 0;
                for(int k = 0;k < j;k++){
                    dp[j] = static_cast<int>((dp[j] % MOD + (1LL * dp[k] * dp[j - k - 1]) % MOD) % MOD);
                }
            }
        }

        return dp[n];
    }

    void input(){
        std::cin >> n >> h;
        std::cout << f2() << std::endl;
    }
}

namespace LongestIncreasingPathInAMatrix{
class Solution {
public:
    std::vector<int> move;
    int longestIncreasingPath(std::vector<std::vector<int>>& matrix) {
        move = {-1, 0, 1, 0, -1};
        int ans{};
        std::vector<std::vector<int>> dp(matrix.size(), std::vector<int>(matrix[0].size(), 0));
        for(int i = 0;i < matrix.size();i++){
            for(int j = 0;j < matrix[0].size();j++){
                ans = std::max(ans, f2(matrix, i, j, dp));
            }
        }
        return ans;
    }

    int f1(std::vector<std::vector<int>>& matrix, int x, int y){
        int ans{};
        for(int i = 0;i < 4;i++){
            int nx = x + move[i];
            int ny = y + move[i + 1];
            if(nx >= 0 && ny >= 0 && nx < matrix.size() && ny < matrix[0].size() && matrix[x][y] < matrix[nx][ny]){
                ans = std::max(ans, f1(matrix, nx, ny));
            }
        }

        return ans + 1;

    }

    int f2(std::vector<std::vector<int>>& matrix, int x, int y, std::vector<std::vector<int>>& dp){
        if(dp[x][y] != 0){
            return dp[x][y];
        }
        int ans{};
        for(int i = 0;i < 4;i++){
            int nx = x + move[i];
            int ny = y + move[i + 1];
            if(nx >= 0 && ny >= 0 && nx < matrix.size() && ny < matrix[0].size() && matrix[x][y] < matrix[nx][ny]){
                ans = std::max(ans, f1(matrix, nx, ny));
            }
        }
        dp[x][y] = ans + 1;
        return dp[x][y];
    }
};
}

namespace DistinctSubsequences{
class Solution {
public: 
    int numDistinct(std::string s, std::string t) {
        int n = static_cast<int>(s.size());
        int m = static_cast<int>(t.size());
        std::vector<std::vector<int>> dp(
            m + 1, std::vector<int>(n + 1, 0));

        for (int i = 0; i <= n; i++) {
            dp[0][i] = 1;
        }

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s[j - 1] == t[i - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] % 1000000007;
                }
                dp[i][j] += dp[i][j - 1] % 1000000007;
            }
        }

        return dp[m][n] % 1000000007;
    }
};
}

int main()
{
    BinaryTree::input();
}