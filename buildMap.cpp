#include <iostream>
#include <vector>

namespace Map1{
    std::vector<std::vector<int>> buildDirect(int n, const std::vector<std::vector<int>>& edges){
        std::vector<std::vector<int>> graph(n, std::vector<int>(n, 0));

        for(auto& edge : edges){
            graph[edge[0]][edge[1]] = 1;
        }

        return graph;
    }

    std::vector<std::vector<int>> buildUndirect(int n, const std::vector<std::vector<int>>& edges){
        std::vector<std::vector<int>> graph(n, std::vector<int>(n, 0));

        for(auto& edge : edges){
            graph[edge[0]][edge[1]] = 1;
            graph[edge[1]][edge[0]] = 1;
        }

        return graph;
    }
}

namespace Map2{
    std::vector<std::vector<int>> buildDirect(int n, const std::vector<std::vector<int>>& edges){
        std::vector<std::vector<int>> graph(n);
        for(auto& edge : edges){
            graph[edge[0]].push_back(edge[1]);
        }

        return graph;
    }

    std::vector<std::vector<int>> buildUndirect(int n, const std::vector<std::vector<int>>& edges){
        std::vector<std::vector<int>> graph(n);
        for(auto& edge : edges){
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        return graph;
    }

}

namespace Map3{
    #define MAX 10000
    std::vector<int> head(MAX);
    std::vector<int> next(MAX);
    std::vector<int> to(MAX);
    int cnt = 1;

    void addEdge(const int start, const int end){
        next[cnt] = head[start];
        to[cnt] = end;
        head[start] = cnt++;
    }

    void buildDirect(int n, const std::vector<std::vector<int>>& edges){
        std::fill(head.begin(), head.end(), 0);
        std::fill(next.begin(), next.end(), 0);
        std::fill(to.begin(), to.end(), 0);
        cnt = 1;
        for(auto& edge : edges){
            addEdge(edge[0], edge[1]);
        }
    }

    void buildUndirect(int n, const std::vector<std::vector<int>>& edges){
        std::fill(head.begin(), head.end(), 0);
        std::fill(next.begin(), next.end(), 0);
        std::fill(to.begin(), to.end(), 0);
        cnt = 1;

        for(auto& edge : edges){
            addEdge(edge[0], edge[1]);
            addEdge(edge[1], edge[0]);
        }
    }
}

int main(){
    Map2::buildDirect(10, {});
}