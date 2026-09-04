#include <iostream>
#include <vector>

namespace NumberOfIslands{
class Solution {
public:
    int numIslands(std::vector<std::vector<char>>& grid) {
        int ans{};
        int n = static_cast<int>(grid.size()), m = static_cast<int>(grid[0].size());
        for(int i = 0;i < n;i++){
            for(int j = 0;j < m;j++){
                if(grid[i][j] == '1'){
                    f(grid, i, j);
                    ans++;
                }
            }
        }
        return ans;
    }

    void f(std::vector<std::vector<char>>& grid, int i, int j){
        if(i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size() || grid[i][j] != '1')return;
        grid[i][j] = '2';
        f(grid, i - 1, j);
        f(grid, i + 1, j);
        f(grid, i, j - 1);
        f(grid, i, j + 1);
    }
};
}

namespace SurroundedRegions{
class Solution {
public:
    void solve(std::vector<std::vector<char>>& board) {
        for(int i = 0;i < board.size();i++){
            for(int j = 0;j < board[0].size();j++){
                if(board[i][j] == 'O' && 
                    (i == 0 || i == board.size() - 1 || j == 0 || j == board[0].size() - 1)){
                    infact(board, i, j);
                }
            }
        }

        for(int i = 0;i < board.size();i++){
            for(int j = 0;j < board[0].size();j++){
                if(board[i][j] == 'O'){
                    board[i][j] = 'X';
                }
                if(board[i][j] == 'F'){
                    board[i][j] = 'O';
                }
            }
        }
    }

    void infact(std::vector<std::vector<char>>& board, int i, int j){
        if(i < 0 || j < 0 || i == board.size() || j == board[0].size() || board[i][j] != 'O'){
            return;
        }

        board[i][j] = 'F';
        infact(board, i - 1, j);
        infact(board, i + 1, j);
        infact(board, i, j - 1);
        infact(board, i, j + 1);
    }
};
}

namespace MakingALargeIsland{
class Solution {
public:
    int largestIsland(std::vector<std::vector<int>>& grid) {
        int n = static_cast<int>(grid.size());
        int m = static_cast<int>(grid[0].size());
        int id = 2;
        for(int i = 0;i < n;i++){
            for(int j = 0;j < m;j++){
                if(grid[i][j] == 1){
                    infact(grid, n, m, i, j, id++);
                }
            }
        }
        int ans{};
        std::vector<int> grounds(id, 0);
        for(int i = 0;i < n;i++){
            for(int j = 0;j < m;j++){
                if(grid[i][j] <= 1)continue;
                ans = std::max(++grounds[grid[i][j]], ans);
            }
        }
        
        std::vector<bool> visit(id, false);
        for(int i = 0;i < n;i++){
            for(int j = 0;j < m;j++){
                if(grid[i][j] != 0)continue;
                int sum{};
                int up = i - 1 < 0 ? 0 : grid[i - 1][j];
                int left = j - 1 < 0 ? 0 : grid[i][j - 1];
                int down = i + 1 == n ? 0 : grid[i + 1][j];
                int right = j + 1 == m ? 0 : grid[i][j + 1];

                if(!visit[up]){
                    sum += grounds[up];
                    visit[up] = true;
                }
                
                if(!visit[down]){
                    sum += grounds[down];
                    visit[down] = true;
                }
                if(!visit[left]){
                    sum += grounds[left];
                    visit[left] = true;
                }
                if(!visit[right]){
                    sum += grounds[right];
                    visit[right] = true;
                }
                ans = std::max(ans, sum + 1);
                visit[up] = false;
                visit[down] = false;
                visit[left] = false;
                visit[right] = false;
            }
        }

        return ans;
    }

    void infact(std::vector<std::vector<int>>& grid, int n, int m, int i, int j, int id){
        if(i < 0 || j < 0 || i == n || j == m || grid[i][j] != 1)return;

        grid[i][j] = id;
        infact(grid, n, m, i - 1, j, id);
        infact(grid, n, m, i + 1, j, id);
        infact(grid, n, m, i, j - 1, id);
        infact(grid, n, m, i, j + 1, id);
    }
};
}

namespace BricksFallingWhenHit{
class Solution {
public:
    int n{}, m{};
    std::vector<int> hitBricks(std::vector<std::vector<int>>& grid, std::vector<std::vector<int>>& hits) {
        n = static_cast<int>(grid.size());
        m = static_cast<int>(grid[0].size());

        for(int i = 0;i < hits.size();i++){
            grid[hits[i][0]][hits[i][1]]--;
        }

        for(int i = 0;i < m;i++){
            if(grid[0][i] == 1){
                infact(grid, 0, i);
            }
        }
        std::vector<int> ans(hits.size(), 0);
        for(int i = hits.size() - 1;i >= 0;i--){
            int row = hits[i][0];
            int col = hits[i][1];
            grid[row][col]++;
            if(worth(grid, row, col)){
                ans[i] = infact(grid, row, col) - 1;
            }
        }
        return ans;
    }

    bool worth(std::vector<std::vector<int>>& grid, int i, int j){
        return grid[i][j] == 1 && 
        (i == 0 || 
        (i > 0) && grid[i - 1][j] == 2 || 
        (i < n - 1) && grid[i + 1][j] == 2 || 
        (j > 0) && grid[i][j - 1] == 2 || 
        (j < m - 1) && grid[i][j + 1] == 2 
        );
    }

    int infact(std::vector<std::vector<int>>& grid, int i, int j){
        if(i < 0 || i == n || j < 0 || j == m || grid[i][j] != 1)return 0;
        grid[i][j] = 2;
        return 1 + infact(grid, i - 1, j) + infact(grid, i + 1, j) + infact(grid, i, j - 1) + infact(grid, i, j + 1);
    }
};
}

int main(){

}