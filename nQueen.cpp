#include <iostream>
#include <vector>
namespace NQueen1{

    bool check(int row, int col, const std::vector<int>& path){
        for(int i = 0;i < row;i++){
            if(path[i] == col || std::abs(row - i) == std::abs(col - path[i])){
                return false;
            }
        }
        return true;
    }

    int process(int row, std::vector<int>& path, int n){
        if(row == n)return 1;
        int ans{};
        for(int col = 0;col < n;col++){
            if(check(row, col, path)){
                path[row] = col;
                ans += process(row + 1, path, n);
            }
            
        }
        return ans;
    }

    int totalNQueens(int n){
        if(n < 1)return 0;
        std::vector<int> path(n, 0);
        return process(0, path, n);
    }
}

namespace NQueen2{

    int process(unsigned long long limit, unsigned long long col, unsigned long long left, unsigned long long right){
        if(col == limit)return 1;

        unsigned long long ban = col | left | right;
        unsigned long long candidate = limit & (~ban);
        int ans{};
        while(candidate != 0){
            unsigned long long place = candidate & (-candidate);
            candidate ^= place;
            ans += process(limit, col | place, ((left | place) >> 1) & limit, ((right | place) << 1) & limit);
        }

        return ans;
    }
    
    int totalNQueens(int n) {
        if (n < 1 || n > 63)return 0;
        unsigned long long limit = (1ULL << n) - 1;
        return process(limit, 0, 0, 0);
    }
}

int main(){
    std::cout << NQueen2::totalNQueens(16) << std::endl;
}