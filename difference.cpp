#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
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

namespace NumMatrix{
    class NumMatrix {
    public:
        typedef int LI;
        std::vector<std::vector<LI>> _matrix;
        LI matrixRowSize{};
        LI matrixColSize{};
        NumMatrix(std::vector<std::vector<LI>>& matrix) {
            matrixRowSize = matrix.size();
            matrixColSize = matrix[0].size();
            _matrix.resize(matrixRowSize + 1, std::vector<int>(matrixColSize + 1));
            for(int i = 0;i < matrix.size();i++){
                for(int j = 0;j < matrix[i].size();j++){
                    _matrix[i + 1][j + 1] = matrix[i][j];
                }
            }

            for(int i = 1;i <= matrixRowSize;i++){
                for(int j = 1;j <= matrixColSize;j++){
                    _matrix[i][j] = sum(i, j);
                }
            }
        }
        
        int sum(int i, int j){
            return _matrix[i][j] + _matrix[i][j - 1] + _matrix[i - 1][j] - _matrix[i - 1][j - 1];
        }

            int sumRegion(int row1, int col1, int row2, int col2) {
                return _matrix[row2 + 1][col2 + 1] - _matrix[row2 + 1][col1] - _matrix[row1][col2 + 1] + _matrix[row1][col1];
            }
    };
}

namespace Largest1BorderedSquare{
    class Solution {
    public:
        typedef int LI;
        typedef std::vector<std::vector<int>> MATRIX;
        LI rowSize{};
        LI colSize{};
        int largest1BorderedSquare(MATRIX& grid) {
            rowSize = grid.size();
            colSize = grid[0].size();
            build(grid);
            if(sum(grid, 0, 0, rowSize - 1, colSize - 1) == 0){
                return 0;
            }
            LI ans = 1;
            for(LI i = 0;i < rowSize;i++){
                for(LI j = 0;j < colSize;j++){
                    for(int c = i + ans, d = j + ans, k = 1 + ans;c < rowSize && d < colSize;c++, d++, k++){
                        if(sum(grid, i, j, c, d) - sum(grid, i + 1, j + 1, c - 1, d - 1) == ((k - 1) << 2)){
                            ans = k;
                        }
                    }
                }
            }

            return ans * ans;
        }

        void build(MATRIX& grid){
            for(LI i = 0;i < rowSize;i++){
                for(LI j = 0;j < colSize;j++){
                    grid[i][j] += get(grid, i - 1, j) + get(grid, i, j - 1) - get(grid, i - 1, j - 1);
                }
            }
        }

        LI get(const MATRIX& grid, LI i, LI j){
            return (i < 0 || j < 0) ? 0 : grid[i][j];
        }

        LI sum(const MATRIX& grid, LI i, LI j, LI c, LI d){
            return get(grid, c, d) - get(grid, c, j - 1) - get(grid, i - 1, d) + get(grid, i - 1, j - 1);
        }
    };
}

namespace TwoDimentionalDifference{
    #define MAX 1002
    typedef long long LI;
    typedef std::vector<std::vector<LI>> MATRIX;
    
    MATRIX matrix(MAX, std::vector<LI>(MAX, 0));

    void set(int x1, int y1, int x2, int y2, int k){
        matrix[x1][y1] += k;
        matrix[x1][y2 + 1] -= k;
        matrix[x2 + 1][y1] -= k;
        matrix[x2 + 1][y2 + 1] += k;
    }

    LI sum(int i, int j){
        return matrix[i][j] + matrix[i - 1][j] + matrix[i][j - 1] - matrix[i - 1][j - 1];
    }

    void build(int n, int m){
        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= m;j++){
                matrix[i][j] = sum(i, j);
            }
        }
    }

    void input(){
        int n{}, m{}, q{};
        std::cin >> n >> m >> q;
        LI b{};
        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= m;j++){
                std::cin >> b;
                set(i, j, i, j, b);
            }
        }
        int x1{}, y1{}, x2{}, y2{}, k{};
        while(q-- > 0){
            std::cin >> x1 >> y1 >> x2 >> y2 >> k;
            set(x1, y1, x2, y2, k);
        }

        build(n, m);

        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= m;j++){
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }

        matrix.clear();
    }
}

namespace Carpet{
    #define MAX 1002
    typedef int LI;
    typedef std::vector<std::vector<LI>> MATRIX;
    
    MATRIX ground(MAX, std::vector<LI>(MAX, 0));

    void set(int x1, int y1, int x2, int y2){
        ground[x1][y1] += 1;
        ground[x1][y2 + 1] -= 1;
        ground[x2 + 1][y1] -= 1;
        ground[x2 + 1][y2 + 1] += 1;
    }

    

    void build(int n){
        for(int i = 1;i <=n;i++){
            for(int j = 1;j <= n;j++){
                ground[i][j] += ground[i - 1][j] + ground[i][j - 1] - ground[i - 1][j - 1];
            }
        }
    }

    void input(){
        int n{}, m{};
        std::cin >> n >> m;
        int x1{}, y1{}, x2{}, y2{};
        for(int i = 0;i < m;i++){
            std::cin >> x1 >> y1 >> x2 >> y2;
            set(x1, y1, x2, y2);
        }

        build(n);
        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= n;j++){
                std::cout << ground[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
}

namespace PossibleToStamp{
    class Solution {
    public:
    std::vector<std::vector<int>> sums;
    std::vector<std::vector<int>> diff;
    int rowSize{};
    int colSize{};
    bool possibleToStamp(std::vector<std::vector<int>>& grid, int stampHeight, int stampWidth) {
        rowSize = static_cast<int>(grid.size());
        colSize = static_cast<int>(grid[0].size());
        sums.assign(rowSize + 2, std::vector<int>(colSize + 2, 0));
        diff.assign(rowSize + 2, std::vector<int>(colSize + 2, 0));
        for(int i = 1;i <= rowSize;i++){
            for(int j = 1;j <= colSize;j++){
                sums[i][j] = grid[i - 1][j - 1];
                sums[i][j] += sums[i - 1][j] + sums[i][j - 1] - sums[i - 1][j - 1];
            }
        }

        for(int i = 0;i < rowSize;i++){
            for(int j = 0;j < colSize;j++){
                if(grid[i][j] == 0 && check(i, j, stampHeight, stampWidth)){
                    set(i, j, stampHeight, stampWidth);
                }
            }
        }
        
        build();

        for(int i = 0;i < rowSize;i++){
            for(int j = 0;j < colSize;j++){
                if(grid[i][j] == 0 && diff[i + 1][j + 1] == 0){
                    return false;
                }
            }
        }

        return true;
    }

    bool check(int a, int b, int stampHeight, int stampWidth){
        a++;
        b++;
        int c = a + stampHeight - 1;
        int d = b + stampWidth - 1;
        if(c > rowSize || d > colSize)return false;
        return sums[c][d] - sums[c][b - 1] - sums[a - 1][d] + sums[a - 1][b - 1] == 0;
    }

    void set(int a, int b, int stampHeight, int stampWidth){
        a++;
        b++;
        int c = a + stampHeight - 1;
        int d = b + stampWidth - 1;
        diff[a][b] += 1;
        diff[c + 1][b] -= 1;
        diff[a][d + 1] -= 1;
        diff[c + 1][d + 1] += 1;
    }

    void build(){
        for(int i = 1;i <= rowSize;i++){
            for(int j = 1;j <= colSize;j++){
                diff[i][j] += diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1];
            }
        }
    }
    };
}

namespace FieldOfGreatestBlessing{
    class Solution {
    public:
        typedef long long LN;
        std::vector<LN> xs;
        std::vector<LN> ys;
        std::vector<std::vector<int>> diff;
        int n{};
        int fieldOfGreatestBlessing(std::vector<std::vector<int>>& forceField) {
            n = static_cast<int>(forceField.size());
            xs.assign(n * 2, 0);
            ys.assign(n * 2, 0);
            
            for(LN i = 0, k = 0, p = 0;i < n;i++){
                LN x = forceField[i][0];
                LN y = forceField[i][1];
                LN r = forceField[i][2];
                xs[k++] = (x << 1) - r;
                xs[k++] = (x << 1) + r;
                ys[p++] = (y << 1) - r;
                ys[p++] = (y << 1) + r;
            }

            int xSize = sort(xs);
            int ySize = sort(ys);

            diff.assign(xSize + 2, std::vector<int>(ySize + 2, 0));
            
            for(int i = 0;i < n;i++){
                LN x = forceField[i][0];
                LN y = forceField[i][1];
                LN r = forceField[i][2];
                int a = rank(xs, (x << 1) - r, xSize);
                int b = rank(ys, (y << 1) - r, ySize);
                int c = rank(xs, (x << 1) + r, xSize);
                int d = rank(ys, (y << 1) + r, ySize);
                
                set(a, b, c, d);
            }

            int ans{};

            for(int i = 1;i <= xSize;i++){
                for(int j = 1;j <= ySize;j++){
                    diff[i][j] += diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1];
                    ans = std::max(ans, diff[i][j]);
                }
            }
            return ans;
        }

        int sort(std::vector<LN>& v){
            std::sort(v.begin(), v.end());
            int size = 0;
            for(int i = 1;i < v.size();i++){
                if(v[i] != v[size]){
                    v[++size] = v[i];
                }
            }

            return size + 1;
        }

        int rank(std::vector<LN>& v, LN num, int size){
            int l{}, r = size - 1;
            int ans{}, m{};
            while(l <= r){ 
                m = (l + r) / 2;
                if(v[m] >= num){
                    ans = m;
                    r = m - 1;
                }else{
                    l = m + 1;
                }
            }
            return ans + 1;
        }

        void set(int a, int b, int c, int d){
            diff[a][b] += 1;
            diff[a][d + 1] -= 1;
            diff[c + 1][b] -= 1;
            diff[c + 1][d + 1] += 1;
        }
    };
}

int main(){
    std::vector<std::vector<int>> grid = {{0, 0, 1}, {1,0,1}};
    std::cout << FieldOfGreatestBlessing::Solution().fieldOfGreatestBlessing(grid) << std::endl;
}