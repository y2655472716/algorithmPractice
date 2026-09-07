#include <iostream>
#include <vector>
#include <algorithm>

namespace P3366K{

    std::vector<int> father(5001, 0);
    std::vector<std::vector<int>> edge(200001, std::vector<int>(3));
    int find(int a){
        if(father[a] != a){
            father[a] = find(father[a]);
        }
        return father[a];
    }

    void _union(int a, int b){
        father[find(a)] = find(b);
    }

    void input(){
        int n{}, m{};
        std::cin >> n >> m;
        for(int i = 1;i <= n;i++){
            father[i] = i;
        }
        long long ans{};
        int count{};
        for(int i = 0;i < m;i++){
            std::cin >> edge[i][0] >> edge[i][1] >> edge[i][2];
        }

        std::sort(edge.begin(), edge.begin() + m, 
            [](const std::vector<int>& v1, const std::vector<int>& v2)
            {return v1[2] < v2[2];}
        );
        for(int i = 0;i < m;i++){
            int from = edge[i][0], to = edge[i][1], weight = edge[i][2];
            if(find(from) != find(to)){
                ans += static_cast<long long>(weight);
                _union(from, to);
                count++;
            }
        }
        if(count == n - 1)
            std::cout << ans << std::endl;
        else
            std::cout << "orz" << std::endl;
    }

}

namespace P3366P1{
    std::vector<int> heap(400001, 0);
    int heapSize{};
    std::vector<bool> visit(5001, false);

    std::vector<int> head(5001, 0);
    std::vector<int> edge(400001, 0);
    std::vector<int> to(400001, 0);
    std::vector<int> weight(400001, 0);
    int cnt = 1;

    void addEdge(int f, int t, int w){
        edge[cnt] = head[f];
        to[cnt] = t;
        weight[cnt] = w;
        head[f] = cnt++;
    }

    void swap(int a, int b){
        int temp = heap[a];
        heap[a] = heap[b];
        heap[b] = temp;
    }

    void heapInsert(int e){
        int cur = heapSize;
        heap[heapSize++] = e;
        
        int up = (cur - 1) / 2;
        while(cur > 0 && weight[heap[up]] > weight[heap[cur]]){
            swap(up, cur);
            cur = up;
            up = (cur - 1) / 2;
        }
    }

    void heapfy(int i){
        int l = i * 2 + 1;
        while(l < heapSize){
            int best = l + 1 < heapSize && weight[heap[l]] > weight[heap[l + 1]] ? l + 1 : l;
            best = weight[heap[best]] < weight[heap[i]] ? best : i;

            if(best == i)break;

            swap(best, i);
            i = best;
            l = i * 2 + 1;
        }
    }

    int Pop(){
        int ans = -1;
        if(heapSize > 0){
            ans = heap[0];
            swap(0, --heapSize);
            heapfy(0);
        }
        return ans;
    }

    void input(){
        int n{}, m{};
        std::cin >> n >> m;
        for(int i = 0;i < m;i++){
            int f{}, t{}, w{};
            std::cin >> f >> t >> w;
            addEdge(f, t, w);
            addEdge(t, f, w);
        }

        int e = head[1];
        while(e != 0){
            heapInsert(e);
            e = edge[e];
        }

        int node = 1;
        visit[1] = true;
        int ans{};
        while(heapSize > 0){
            e = Pop();
            int t = to[e], w = weight[e];
            if(!visit[t]){
                ans += w;
                node++;
                e = head[t];
                while(e != 0){
                    heapInsert(e);
                    e = edge[e];
                }
                visit[t] = true;
            }
        }

        if(node == n)std::cout << ans << std::endl;
        else std::cout << "orz" << std::endl;
        
    }
}

namespace P3366P2{
    #define MAXN 5001
    #define MAXE 400001
    std::vector<int> head(MAXN, 0);
    std::vector<int> next(MAXE, 0);
    std::vector<int> to(MAXE, 0);
    std::vector<int> weight(MAXE, 0);
    int cnt = 1;
    void addEdge(int f, int t, int w){
        next[cnt] = head[f];
        to[cnt] = t;
        weight[cnt] = w;
        head[f] = cnt++;
    }
    std::vector<std::vector<int>> heap(MAXN, std::vector<int>(2, 0));
    int heapSize{};
    int no{}, we{};

    std::vector<int> where(MAXN, -1);
    int nodeCnt{};

    void swap(int a, int b){
        where[heap[a][0]] = b;
        where[heap[b][0]] = a;
        int tempn = heap[a][0];
        int tempw = heap[a][1];
        heap[a][0] = heap[b][0];
        heap[a][1] = heap[b][1];
        heap[b][0] = tempn;
        heap[b][1] = tempw;

    }

    void heapInsert(int i){
        while(i > 0 && heap[(i - 1) / 2][1] > heap[i][1]){
            swap((i - 1) / 2, i);
            i = (i - 1) / 2;
        }
    }

    void heapfy(int i){
        int l = i * 2 + 1;
        while(l < heapSize){
            int best = l + 1 < heapSize && heap[l][1] > heap[l + 1][1] ? l + 1 : l;
            best = heap[best][1] < heap[i][1] ? best : i;
            if(best == i)break;

            swap(i, best);
            i = best;
            l = i * 2 + 1;
        }
    }

    void Pop(){
        if(heapSize == 0)return;
        no = heap[0][0];
        we = heap[0][1];
        swap(0, --heapSize);
        heapfy(0);
    }



    void addOrUpdateOrIgnore(int ei){
        int t = to[ei];
        if(where[t] == -1){
            heap[heapSize][0] = t;
            heap[heapSize][1] = weight[ei];
            where[t] = heapSize;
            heapSize++;
            heapInsert(where[t]);
        }else if(where[t] != -2){
            heap[where[t]][1] = std::min(heap[where[t]][1], weight[ei]);
            heapInsert(where[t]);
        }
    }

    int prim(){
        nodeCnt = 1;
        where[1] = -2;
        for(int ei = head[1];ei != 0;ei = next[ei]){
            addOrUpdateOrIgnore(ei);
        }
        int ans{};
        while(heapSize > 0){
            Pop();
            nodeCnt++;
            where[no] = -2;
            ans += we;
            for(int ei = head[no];ei != 0;ei = next[ei]){
                addOrUpdateOrIgnore(ei);
            }
        }

        return ans;
    }

    void input(){
        std::fill(head.begin(), head.end(), 0);
        std::fill(next.begin(), next.end(), 0);
        std::fill(to.begin(), to.end(), 0);
        std::fill(weight.begin(), weight.end(), 0);
        std::fill(where.begin(), where.end(), -1);
        cnt = 1;
        nodeCnt = 0;
        int n{}, m{};
        std::cin >> n >> m;
        for(int i = 0;i < m;i++){
            int f{}, t{}, w{};
            std::cin >> f >> t >> w;
            addEdge(f, t, w);
            addEdge(t, f, w);
        }
        int ans = prim();
        if(nodeCnt == n){
            std::cout << ans << std::endl;
        }else{
            std::cout << "orz" << std::endl;
        }
    }
}

namespace P1194I{
    #define MAXA 1001
    std::vector<int> father(MAXA, 0);
    std::vector<std::vector<int>> edge(250001, std::vector<int>(3));
    int edgeCount{};
    int find(int a){
        if(father[a] != a){
            father[a] = find(father[a]);
        }
        return father[a];
    }

    void _union(int a, int b){
        father[find(a)] = find(b);
    }

    bool isSameSet(int a, int b){
        return find(a) == find(b);
    }

    void input(){
        int A{}, B{};
        std::cin >> A >> B;
        int k{};
        for(int i = 0;i < B;i++){
            father[i] = i;
        }
        for(int i = 0;i < B;i++){
            for(int j = 0;j < B;j++){
                std::cin >> k;
                if(i <= j && k != 0){
                    edge[edgeCount][0] = i;
                    edge[edgeCount][1] = j;
                    edge[edgeCount][2] = k;
                    edgeCount++;
                }
            }
        }

        std::sort(edge.begin(), edge.begin() + edgeCount, 
            [](const std::vector<int>& e1, const std::vector<int>& e2){return e1[2] < e2[2];}
        );
        int ans = B * A;
        for(int i = 0;i < edgeCount;i++){
            if(!isSameSet(edge[i][0], edge[i][1])){
                ans -= A < edge[i][2] ? 0 : A - edge[i][2];
                _union(edge[i][0], edge[i][1]);
            }
        }

        std::cout << ans << std::endl;
    }
}

namespace P1194II{
    struct Edge{
        int from{};
        int to{};
        int weight{};
    };
    std::vector<int> father(501, 0);
    std::vector<Edge> edges(125250);
    int edgeCount{};

    int find(int a){
        if(father[a] != a){
            father[a] = find(father[a]);
        }
        return father[a];
    }

    void _union(int a, int b){
        father[find(a)] = find(b);
    }

    void input(){
        int A{}, B{};
        std::cin >> A >> B;
        int k{};
        for(int i = 0;i < B;i++){
            for(int j = 0;j < B;j++){
                std::cin >> k;
                if(i <= j && k != 0){
                    edges[edgeCount].from = i;
                    edges[edgeCount].to = j;
                    edges[edgeCount++].weight = k;
                }
            }
        }

        for(int i = 0;i < B;i++){
            edges[edgeCount].from = B;
            edges[edgeCount].to = i;
            edges[edgeCount++].weight = A;
        }
        for(int i = 0;i <= B;i++){
            father[i] = i;
        }
        std::sort(edges.begin(), edges.begin() + edgeCount, [](Edge& e1, Edge& e2){return e1.weight < e2.weight;});
        int ans{};
        for(int i = 0;i < edgeCount;i++){
            if(find(edges[i].from) != find(edges[i].to)){
                ans += edges[i].weight;
                _union(edges[i].from, edges[i].to);
            }
        }

        std::cout << ans << std::endl;
    }
}

namespace CheckingExistenceOfEdgeLengthLimitedPaths{
class Solution {
public:
    std::vector<int> father;
    std::vector<bool> distanceLimitedPathsExist(int n, std::vector<std::vector<int>>& edgeList, std::vector<std::vector<int>>& queries) {
        int k = static_cast<int>(queries.size());
        std::vector<std::vector<int>> query(k, std::vector<int>(4));
        for(int i = 0;i < k;i++){
            query[i][0] = queries[i][0];
            query[i][1] = queries[i][1];
            query[i][2] = queries[i][2];
            query[i][3] = i;
        }
        father.assign(n, 0);
        for(int i = 0;i < n;i++){father[i] = i;}
        std::sort(query.begin(), query.end(), 
        [](const std::vector<int>& q1, const std::vector<int>& q2){return q1[2] < q2[2];});
        std::sort(edgeList.begin(), edgeList.end(), 
        [](const std::vector<int>& e1, const std::vector<int>& e2){return e1[2] < e2[2];});
        std::vector<bool> ans(k, false);
        for(int i = 0, j = 0;i < k;i++){
            for(;j < edgeList.size() && edgeList[j][2] < query[i][2];j++){
                _union(edgeList[j][0], edgeList[j][1]);
            }
            ans[query[i][3]] = isSameSet(query[i][0], query[i][1]);
        }

        return ans;
    }

    int find(int a){
        if(father[a] != a){
            father[a] = find(father[a]);
        }
        return father[a];
    }

    void _union(int a, int b){
        father[find(a)] = find(b);
    }

    bool isSameSet(int a, int b){
        return find(a) == find(b);
    }
};
}

namespace P2330{
    std::vector<int> father(301, 0);
    std::vector<std::vector<int>> edges(8001, std::vector<int>(3, 0));
    int find(int a){
        if(father[a] != a){
            father[a] = find(father[a]);
        }
        return father[a];
    }

    void _union(int a, int b){
        father[find(a)] = find(b);
    }

    void input(){
        int n{}, m{};
        std::cin >> n >> m;
        for(int i = 0;i < m;i++){
            std::cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
        }
        for(int i = 1;i <= n;i++){
            father[i] = i;
        }
        int cnt{};
        int max{};
        std::sort(edges.begin(), edges.begin() + m, [](std::vector<int>& e1, std::vector<int>& e2){return e1[2] < e2[2];});
        for(int i = 0;i < m;i++){
            if(find(edges[i][0]) != find(edges[i][1])){
                cnt++;
                max = std::max(edges[i][2], max);
                _union(edges[i][0], edges[i][1]);
            }
        }

        std::cout << cnt << " " << max << std::endl;
    }
}

int main(){
    P1194II::input();
}