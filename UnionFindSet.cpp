#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <unordered_set>

namespace ClassicUnionFindSet1{
    #define CMAX 1000001
    std::vector<int> father(CMAX, 0);
    std::vector<int> size(CMAX, 0);
    std::vector<int> stack(CMAX, 0);
    int top{};
    void init(int N){
        for(int i = 0;i < N;i++){
            father[i] = i;
        }
        top = 0;
        std::fill(size.begin(), size.begin() + N, 1);
    }

    int find(int target){
        while(father[target] != target){
            stack[top++] = target;
            target = father[target];
        }

        while(top > 0){
            father[stack[--top]] = target;
        }

        return target;
    }

    bool isSameSet(int a, int b){
        return find(a) == find(b);
    }

    void _union(int a, int b){
        int af = find(a);
        int bf = find(b);
        if(af == bf)return;

        int more = size[af] >= size[bf] ? af : bf;
        int less = more == af ? bf : af;
        father[less] = more;
        size[more] += size[less];
    }

    void input(){
        int N{}, M{};
        std::cin >> N >> M;
        init(N);
        int opt{};
        int x{}, y{};
        for(int i = 0;i < M;i++){
            std::cin >> opt;
            std::cin >> x >> y;
            if(opt == 1){
                std::cout << (isSameSet(x - 1, y - 1) ? "Yes" : "No") << std::endl;
            }else{
                _union(x - 1, y - 1);
            }
        }
    }
}

namespace ClassicUnionFindSet2{
    #define CMAX2 1000001
    std::vector<int> father(CMAX2, 0);
    void init(int N){
        for(int i = 1;i <= N;i++){
            father[i] = i;
        }
    }

    int find(int a){
        if(father[a] != a){
            father[a] = find(father[a]);
        }
        return father[a];
    }

    bool isSameSet(int a, int b){
        return find(a) == find(b);
    }

    void _union(int a, int b){
        father[find(a)] = find(b);
    }

    void input(){
        int N{}, M{};
        std::cin >> N >> M;
        init(N);
        int Z{}, X{}, Y{};
        for(int i = 0;i < M;i++){
            std::cin >> Z >> X >> Y;
            if(Z == 1){
                _union(X, Y);
            }else{
                std::cout << (isSameSet(X, Y) ? "Y" : "N") << std::endl;
            }
        }
    }
}

namespace CouplesHoldingHands{
class Solution {
public:
    std::vector<int> father;
    int set{};
    int minSwapsCouples(std::vector<int>& row) {
        int n = static_cast<int>(row.size());
        build(n / 2);

        for(int i = 0;i < n;i+= 2){
            _union(row[i] / 2, row[(i + 1)] / 2);
        }

        return n / 2 - set;
    }

    void build(int n){
        father.resize(n + 1, 0);
        for(int i = 0;i < n;i++){
            father[i] = i;
        }
        set = n;
    }

    int find(int a){
        if(father[a] != a){
            father[a] = find(father[a]);
        }
        return father[a];
    }

    void _union(int a, int b){
        int af = find(a);
        int bf = find(b);
        if(af != bf){
            father[af] = bf;
            set--;
        }
    }
};
}

namespace SimilarStringGroups{
class Solution {
public:
    std::vector<int> father;
    int set{};
    int numSimilarGroups(std::vector<std::string>& strs) {
        int n = static_cast<int>(strs.size());
        build(n);
        for(int i = 0;i < n;i++){
            for(int j = i + 1;j < n;j++){
                if(find(i) != find(j) && can(strs[i], strs[j])){
                   _union(i, j); 
                }
            }
        }

        return set;
    }

    bool can(std::string& s1, std::string& s2){
        int diff{};
        for(int i = 0;i < s1.size() && diff < 3;i++){
            if(s1[i] != s2[i])diff++;
        }
        return diff == 0 || diff == 2;
    }

    void build(int n){
        father.resize(n);
        for(int i = 0;i < n;i++){
            father[i] = i;
        }
        set = n;
    }

    int find(int a){
        if(father[a] != a){
            father[a] = find(father[a]);
        }
        return father[a];
    }

    void _union(int a, int b){
        int af = find(a);
        int bf = find(b);
        if(af != bf){
            father[af] = bf;
            set--;
        }
    }
}; 
}

namespace NumberOfIslands{
class Solution {
public:
    std::vector<int> father;
    int row{}, col{};
    int set{};
    int numIslands(std::vector<std::vector<char>>& grid) {
        set = 0;
        row = static_cast<int>(grid.size());
        col = static_cast<int>(grid[0].size());
        father.resize(row * col, 0);
        for(int i = 0;i < row;i++){
            for(int j = 0;j < col;j++){
                if(grid[i][j] == '1'){
                    int in = index(i, j);
                    father[in] = in;
                    set++;
                }
            }
        }

        for(int i = 0;i < row;i++){
            for(int j = 0;j < col;j++){
                if(grid[i][j] == '1'){
                    if(i > 0 && grid[i - 1][j] == '1'){
                        _union(index(i, j), index(i - 1, j));
                    }
                    if(j > 0 && grid[i][j - 1] == '1'){
                        _union(index(i, j), index(i, j - 1));
                    }
                }
            }
        }

        return set;
    }

    int index(int i, int j){
        return i * col + j;
    }

    int find(int a){
        if(father[a] != a){
            father[a] = find(father[a]);
        }
        return father[a];
    }

    void _union(int a, int b){
        int af = find(a);
        int bf = find(b);
        if(af != bf){
            father[af] = bf;
            set--;
        }
    }
};
}

namespace MostStonesRemovedWithSameRowOrColumn{
class Solution {
public:
    std::vector<int> father;
    std::unordered_map<int, int> rowMap;
    std::unordered_map<int, int> colMap;
    int set{};
    int removeStones(std::vector<std::vector<int>>& stones) {
        int n = static_cast<int>(stones.size());
        father.resize(n + 1, 0);
        set = n;

        for(int i = 0;i <= n;i++){
            father[i] = i;
        }

        for(int i = 0;i < n;i++){
            if(rowMap.find(stones[i][0]) == rowMap.end()){
                rowMap[stones[i][0]] = i;
            }else{
                _union(i, rowMap[stones[i][0]]);
            }

            if(colMap.find(stones[i][1]) == colMap.end()){
                colMap[stones[i][1]] = i;
            }else{
                _union(i, colMap[stones[i][1]]);
            }
        }

        return n - set;
    }

    int find(int a){
        if(father[a] != a){
            father[a] = find(father[a]);
        }
        return father[a];
    }

    void _union(int a, int b){
        int fa = find(a);
        int fb = find(b);
        if(fa != fb){
            father[fa] = fb;
            set--;
        }
    }
};
}

namespace FindAllPeopleWithSecret{
class Solution {
public:
    std::vector<int> father;
    std::vector<int> secret;
    std::vector<int> findAllPeople(int n, std::vector<std::vector<int>>& meetings, int firstPerson) {
        build(n);
        int m = static_cast<int>(meetings.size());
        std::sort(meetings.begin(), meetings.end(), 
            [](const std::vector<int>& v1, const std::vector<int>& v2){
                return v1[2] < v2[2];
            });
        _union(0, firstPerson);
        for(int l{}, r{};l < m;){
            r = l;
            while(r + 1 < m && meetings[r + 1][2] == meetings[l][2]){
                r++;
            }

            for(int i = l;i <= r;i++){
                _union(meetings[i][0], meetings[i][1]);
            }

            for(int i = l;i <= r;i++){
                int a = meetings[i][0];
                int b = meetings[i][1];
                if(!secret[find(a)]){
                    father[a] = a;
                }

                if(!secret[find(b)]){
                    father[b] = b;
                }
            }
            l = r + 1;
        }
        std::vector<int> ans(n);
        int top{};
        for(int i = 0;i < n;i++){
            
            if(secret[find(i)]){
                ans[top++] = i;
            }
        }
        ans.resize(top);
        return ans;
    }

    void build(int n){
        father.resize(n, 0);
        secret.resize(n, false);
        for(int i = 0;i < n;i++){
            father[i] = i;
        }
        secret[0] = true;
    }

    int find(int a){
        if(father[a] != a){
            father[a] = find(father[a]);
        }

        return father[a];
    }

    void _union(int a, int b){
        int fa = find(a);
        int fb = find(b);
        father[fa] = fb;
        secret[fb] |= secret[fa];
    }
};
}

namespace NumberOfGoodPaths{
class Solution {
public:
    std::vector<int> father;
    std::vector<int> setMaxSize;
    int numberOfGoodPaths(std::vector<int>& vals, std::vector<std::vector<int>>& edges) {
        int ns = static_cast<int>(vals.size());
        int es = static_cast<int>(edges.size());
        build(ns);
        std::sort(edges.begin(), edges.end(), 
            [&vals](const std::vector<int>& e1, const std::vector<int>& e2){
                int e1_max = std::max(vals[e1[0]], vals[e1[1]]);
                int e2_max = std::max(vals[e2[0]], vals[e2[1]]);
                return e1_max < e2_max;
            });
        int ans{};
        for(int i = 0;i < es;i++){
            ans += _union(edges[i][0], edges[i][1], vals);
        }

        return ans + ns;
    }

    void build(int n){
        father.resize(n, 0);
        setMaxSize.resize(n, 1);
        for(int i = 0;i < n;i++){
            father[i] = i;
        }
    }

    int find(int a){
        if(father[a] != a){
            father[a] = find(father[a]);
        }
        return father[a];
    }

    int _union(int a, int b, std::vector<int>& vals){
        int fa = find(a);
        int fb = find(b);
        int path{};
        if(fa != fb){
            if(vals[fa] > vals[fb]){
                father[fb] = fa;
            }else if(vals[fa] < vals[fb]){
                father[fa] = fb;
            }else{
                path = setMaxSize[fa] * setMaxSize[fb];
                father[fa] = fb;
                setMaxSize[fb] += setMaxSize[fa];
            }
        }

        return path;
    }

};
}

namespace MinimizeMalwareSpread{
class Solution {
public:
    std::vector<int> father;
    std::vector<int> setSize;
    std::vector<int> origins;
    std::vector<bool> virus;
    int minMalwareSpread(std::vector<std::vector<int>>& graph, std::vector<int>& initial) {
        int n = static_cast<int>(graph.size());
        build(n);
        for(auto& v : initial){
            virus[v] = true;
        }

        for(int i = 0;i < n;i++){
            for(int j = 0;j < n;j++){
                if(graph[i][j] == 1 && !virus[i] && !virus[j]){
                _union(i, j);
                }
            }
        }

        for(auto& sick : initial){
            for(int ni = 0;ni < n;ni++){
                if(!virus[ni] && graph[sick][ni]){
                    int fn = find(ni);
                    if(origins[fn] == -1){
                        origins[fn] = sick;
                    }else if(origins[fn] != sick){
                        origins[fn] = -2;
                    }
                }
            }
        }

        int ans = initial[0], ans_max = -1;
        for(auto& sick : initial){
            int sum{};
            for(int j = 0;j < n;j++){
                if(j == find(j) && origins[j] == sick){
                    sum += setSize[j];
                }
            }

            if(ans_max < sum || (ans_max == sum && ans > sick)){
                ans = sick;
                ans_max = sum;
            }
        }

        return ans;
    }

    void build(int n){
        father.resize(n, 0);
        setSize.resize(n, 1);
        for(int i = 0;i < n;i++){
            father[i] = i;
        }
        origins.resize(n, -1);
        virus.resize(n, false);
    }

    int find(int a){
        if(father[a] != a){
            father[a] = find(father[a]);
        }

        return father[a];
    }

    void _union(int a, int b){
        int fa = find(a);
        int fb = find(b);
        if(fa != fb){
            father[fa] = fb;
            setSize[fb] += setSize[fa];
        }
    }
};
}

int main(){
    std::vector<std::vector<int>> v = {{3,1,3}, {1,2,2}, {0,3,3}};
    FindAllPeopleWithSecret::Solution().findAllPeople(4, v, 3);
}