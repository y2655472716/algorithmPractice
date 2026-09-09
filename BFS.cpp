#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <deque>
#include <queue>


namespace AsFarFromLandAsPossible{
class Solution {
public:
    int maxDistance(std::vector<std::vector<int>>& grid) {
        int n = static_cast<int>(grid.size());
        std::vector<std::vector<bool>> visit(n, std::vector<bool>(n, false));
        std::vector<std::vector<int>> queue(n * n, std::vector<int>(2));
        int front{}, end{};
        int level{}, cnt{};
        int seas{};
        for(int i = 0;i < n;i++){
            for(int j = 0;j < n;j++){
                if(grid[i][j] == 1){
                    queue[end][0] = i;
                    queue[end++][1] = j;
                    cnt++;
                    visit[i][j] = true;
                }else{
                    seas++;
                }
            }
        }

        if(seas == 0 || seas == n * n){
            return -1;
        }

        while(front < end){
            cnt = end - front;
            for(int i = 0;i < cnt;i++){
                int x = queue[front][0];
                int y = queue[front++][1];

                if(x - 1 >= 0 && !visit[x - 1][y]){
                    queue[end][0] = x - 1;
                    queue[end++][1] = y;
                    visit[x - 1][y] = true;
                }
                if(x + 1 < n && !visit[x + 1][y]){
                    queue[end][0] = x + 1;
                    queue[end++][1] = y;
                    visit[x + 1][y] = true;
                }
                if(y - 1 >= 0 && !visit[x][y - 1]){
                    queue[end][0] = x;
                    queue[end++][1] = y - 1;
                    visit[x][y - 1] = true;
                }
                if(y + 1 < n && !visit[x][y + 1]){
                    queue[end][0] = x;
                    queue[end++][1] = y + 1;
                    visit[x][y + 1] = true;
                }
            }
            level++;
        }

        return level - 1;
    }
};
}

namespace StickersToSpellWord{
class Solution {
public:
    int minStickers(std::vector<std::string>& stickers, std::string target) {
        std::vector<std::vector<std::string>> graph(26);
        std::vector<std::string> queue(401);
        std::unordered_set<std::string> visit;
        int l{}, r{};
        std::sort(target.begin(), target.end());
        for(auto& sticker : stickers){
            std::sort(sticker.begin(), sticker.end());
            for(int i = 0;i < sticker.size();i++){
                if(i == 0 || sticker[i] != sticker[i - 1]){
                    graph[sticker[i] - 'a'].push_back(sticker);
                }
            }
        }

        visit.insert(target);
        queue[r++] = target;
        int level = 1;
        while(l < r){
            int size = r - l;
            for(int i = 0;i < size;i++){
                for(auto& str : graph[queue[l][0] - 'a']){
                    std::string next = move(queue[l], str);
                    if(next.empty())return level;
                    if(visit.find(next) == visit.end()){
                        queue[r++] = next;
                        visit.insert(next);
                    }
                    
                }
                l++;
            }
            
            level++;
        }

        return -1;
    }

    std::string move(std::string& f, std::string& s){
        int fp{}, sp{};
        std::string ans{};
        while(fp < f.size() && sp < s.size()){
            if(f[fp] < s[sp]){
                ans.insert(ans.end(), f[fp]);
                fp++;
            }
            if(f[fp] == s[sp]){
                fp++;
                sp++;
            }
            if(f[fp] > s[sp]){
                sp++;
            }
        }

        while(fp < f.size()){
            ans.insert(ans.end(), f[fp++]);
        }
        return ans;
    }
};
}

namespace MinimumObstacleRemovalToReachCorner{
class Solution {
public:
    int minimumObstacles(std::vector<std::vector<int>>& grid) {
        std::vector<int> move = {-1, 0, 1, 0, -1};
        int m = static_cast<int>(grid.size());
        int n = static_cast<int>(grid[0].size());
        std::deque<std::pair<int, int>> queue; 
        std::vector<std::vector<int>> distance(m, std::vector<int>(n, INT_MAX - 1));
        
        queue.push_front({0, 0});
        distance[0][0] = 0;
        while(!queue.empty()){
            int x = queue.front().first;
            int y = queue.front().second;
            queue.pop_front();
            if(x == m - 1 && y == n - 1)return distance[x][y];
            for(int i = 0;i < 4;i++){
                int nx = x + move[i];
                int ny = y + move[i + 1];
                if(nx >= 0 && ny >= 0 && nx < m && ny < n){
                    if(distance[nx][ny] > distance[x][y] + grid[nx][ny]){
                        distance[nx][ny] = distance[x][y] + grid[nx][ny];
                        if(grid[nx][ny] == 0){
                            queue.push_front({nx, ny});
                        }else{
                            queue.push_back({nx, ny});
                        }
                    }
                }
            }
        }

        return distance[m - 1][n - 1];
    }
};
}

namespace MinimumCostToMakeAtLeastOneValidPathInAGrid{
class Solution {
public:
    int minCost(std::vector<std::vector<int>>& grid) {
        std::vector<std::pair<int, int>> move = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        int m = static_cast<int>(grid.size());
        int n = static_cast<int>(grid[0].size());
        std::vector<std::vector<int>> costs(m, std::vector<int>(n, INT_MAX - 1));
        std::deque<std::pair<int, int>> q;

        q.emplace_back(0, 0);
        costs[0][0] = 0;
        while(!q.empty()){
            int x = q.front().first;
            int y = q.front().second;
            q.pop_front();
            if(x == m - 1 && y == n - 1)return costs[x][y];

            for(int i = 0;i < 4;i++){
                int nx = x + move[i].first;
                int ny = y + move[i].second;
                int w = grid[x][y] - 1 == i ? 0 : 1;
                if(nx >= 0 && ny >= 0 && nx < m && ny < n){
                    if(costs[nx][ny] > costs[x][y] + w){
                        costs[nx][ny] = costs[x][y] + w;
                        if(w == 0){
                            q.emplace_front(nx, ny);
                        }else{
                            q.emplace_back(nx, ny);
                        }
                    }
                }
            }
        }
        return costs[m - 1][n - 1];
    }
};
}

namespace TrappingRainWater{
class Solution {
public:
    struct Column{
        int x{};
        int y{};
        int height{};

        Column(){}
        Column(int nx, int ny, int nh) : x(nx), y(ny), height(nh){}
    };
    int trapRainWater(std::vector<std::vector<int>>& heightMap) {
        if(heightMap.empty() || heightMap[0].empty())return 0;
        std::vector<int> move = {-1, 0, 1, 0, -1};
        int m = static_cast<int>(heightMap.size());
        int n = static_cast<int>(heightMap[0].size());
        auto cmp = [](const Column& c1, const Column& c2){return c1.height > c2.height;};
        std::priority_queue<Column, std::vector<Column>, 
            decltype(cmp)> heap(cmp);
        std::vector<std::vector<bool>> visit(m, std::vector<bool>(n, false));
        for(int i = 0;i < n;i++){
            if(!visit[0][i]){
                heap.emplace(0, i, heightMap[0][i]);
                visit[0][i] = true;
            } 
            
            if(!visit[m - 1][i]){
                heap.emplace(m - 1, i, heightMap[m - 1][i]);
                visit[m - 1][i] = true;
            }
        }

        for(int i = 0;i < m;i++){
            if(!visit[i][0]){
                heap.emplace(i, 0, heightMap[i][0]);
                visit[i][0] = true;
            } 
            
            if(!visit[i][n - 1]){
                heap.emplace(i, n - 1, heightMap[i][n - 1]);
                visit[i][n - 1] = true;
            }
        }
        int ans{};
        while(!heap.empty()){
            int x = heap.top().x;
            int y = heap.top().y;
            int h = heap.top().height;
            ans += h - heightMap[x][y];
            heap.pop();
            for(int i = 0;i < 4;i++){
                int nx = x + move[i];
                int ny = y + move[i + 1];
                if(nx >= 0 && ny >= 0 && nx < m && ny < n && !visit[nx][ny]){
                    heap.emplace(nx, ny, std::max(heightMap[nx][ny], h));
                    visit[nx][ny] = true;
                }
            }
        }

        return ans;

    }
};
}

namespace WordLadder{
class Solution {
public:
    std::vector<std::vector<std::string>> findLadders(\
        std::string beginWord, std::string endWord, std::vector<std::string>& wordList\
    ) {
        
    }
};
}

int main(){
    std::vector<std::vector<int>> v = {{1,1,1,1}, {2,2,2,2}, {1, 1, 1, 1}, {2, 2, 2, 2}};
    std::cout << MinimumCostToMakeAtLeastOneValidPathInAGrid::Solution().minCost(v);
}