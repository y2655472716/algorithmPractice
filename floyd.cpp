#include <iostream>
#include <vector>
#include <climits>

namespace P2910{
    #define MAXA 10001
    #define MAXN 101
    std::vector<int> mast(MAXA, 0);
    std::vector<std::vector<int>> distance(MAXN, std::vector<int>(MAXN, INT_MAX));

        void floyd(int N, int M){
        for(int bridge = 1;bridge <= N;bridge++){
            for(int i = 1;i <= N;i++){
                for(int j = 1;j <= N;j++){
                    if(distance[i][bridge] + distance[bridge][j] < distance[i][j]){
                        distance[i][j] = distance[i][bridge] + distance[bridge][j];
                    }
                }
            }
        }
    }

    void input(){
        int N{}, M{};
        std::cin >> N >> M;
        for(int i = 0;i < M;i++){
            std::cin >> mast[i];
        }

        for(int i = 1;i <= N;i++){
            for(int j = 1;j <= N;j++){
                std::cin >> distance[i][j];
            }
        }

        floyd(N, M);
        int ans{};
        for(int i = 0;i < M - 1;i++){
            if(distance[mast[i]][mast[i + 1]] == INT_MAX){
                std::cout << -1 << std::endl;
                return;
            }

            ans += distance[mast[i]][mast[i + 1]];

        }

        std::cout << ans << std::endl;
    }


}

namespace CheapestFlightsWithinKStops{
class Solution {
public:
    int findCheapestPrice(int n, std::vector<std::vector<int>>& flights, int src, int dst, int k) {
        std::vector<int> cur(n, INT_MAX);
        cur[src] = 0;
        std::vector<int> next = cur;
        for(int i = 0;i <= k;i++){
            for(auto& flight : flights){
                int from = flight[0];
                int to = flight[1];
                int price = flight[2];
                if(cur[from] != INT_MAX){
                    next[to] = std::min(next[to], cur[from] + price);
                }
            }

            cur = next;
        }

        return cur[dst] == INT_MAX ? -1 : cur[dst];
    }
};
}

namespace P3385{
    #define MAXQ 2000001
    #define MAXN 2001
    #define MAXM 3001
    std::vector<int> distance(MAXN, INT_MAX);
    std::vector<int> head(MAXN, 0);
    std::vector<int> next(MAXM * 2, 0);
    std::vector<int> to(MAXM * 2, 0);
    std::vector<int> weight(MAXM * 2, 0);
    std::vector<int> changeCnt(MAXN, 0);
    int cnt = 1;
    std::vector<int> queue(MAXQ, 0);
    std::vector<bool> enter(MAXN, false);
    int l{}, r{};
    void build(){
        std::fill(distance.begin(), distance.end(), INT_MAX);  
        std::fill(head.begin(), head.end(), 0);
        std::fill(changeCnt.begin(), changeCnt.end(), 0);
        std::fill(enter.begin(), enter.end(), false);
        cnt = 1;
        l = r = 0;
    }

    bool bellman_ford(int n){
        distance[1] = 0;
        queue[r++] = 1;
        enter[1] = true;
        changeCnt[1]++;
        while(l < r){
            int from = queue[l++];
            enter[from] = false;

            for(int edge = head[from];edge != 0;edge = next[edge]){
                int t = to[edge];
                int wei = weight[edge];
                if(distance[t] > distance[from] + wei){
                    distance[t] = distance[from] + wei;
                    if(!enter[t]){
                        if(changeCnt[t] == n)return true;

                        queue[r++] = t;
                        enter[t] = true;
                        changeCnt[t]++;
                    }
                }
            }
        }

        return false;
    }

    void addEdge(int f, int t, int w){
        next[cnt] = head[f];
        to[cnt] = t;
        weight[cnt] = w;
        head[f] = cnt++;
    }

    void input(){
        int T{};
        std::cin >> T;
        for(int i = 0;i < T;i++){
            build();
            int n{}, m{};
            std::cin >> n >> m;
            for(int j = 0;j < m;j++){
                int u{}, v{}, w{};
                std::cin >> u >> v >> w;
                if(w >= 0){
                    addEdge(v, u, w);
                }

                addEdge(u, v, w);
            }

            std::cout << (bellman_ford(n) ? "YES" : "NO") << std::endl;
        }
    }
}

int main(){
    P3385::input();
}