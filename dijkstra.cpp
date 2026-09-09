#include <iostream>
#include <vector>
#include <climits>
#include <queue>

namespace P4799
{
#define MAXN 100001
#define MAXM 200001
    std::vector<int> head(MAXN, 0);
    std::vector<int> next(MAXM, 0);
    std::vector<int> to(MAXM, 0);
    std::vector<int> weight(MAXM, 0);
    int cnt = 1;
    std::vector<int> distance(MAXN, INT_MAX);
    std::vector<std::pair<int, int>> heap(MAXN);
    int heapSize{};
    std::vector<int> where(MAXN, -1);
    void addEdge(int f, int t, int w)
    {
        next[cnt] = head[f];
        to[cnt] = t;
        weight[cnt] = w;
        head[f] = cnt++;
    }

    void swap(int a, int b)
    {
        where[heap[a].first] = b;
        where[heap[b].first] = a;
        auto temp = heap[a];
        heap[a] = heap[b];
        heap[b] = temp;
    }

    void heapInsert(int i)
    {
        while (i > 0 && heap[(i - 1) >> 1].second > heap[i].second)
        {
            swap((i - 1) >> 1, i);
            i = (i - 1) >> 1;
        }
    }

    void heapify(int i)
    {
        int l = (i << 1) + 1;
        while (l < heapSize)
        {
            int best = l + 1 < heapSize && heap[l + 1].second < heap[l].second ? l + 1 : l;
            best = heap[best].second < heap[i].second ? best : i;
            if (best == i)
                break;

            swap(best, i);
            i = best;
            l = (i << 1) + 1;
        }
    }

    void pop()
    {
        int p = heap[0].first;
        swap(0, --heapSize);
        heapify(0);
        where[p] = -2;
    }

    void addOrUpdateOrIgnore(int x, int w)
    {
        if (where[x] == -1)
        {
            heap[heapSize] = {x, w};
            where[x] = heapSize++;
            heapInsert(where[x]);
        }
        else if (where[x] >= 0)
        {
            heap[where[x]].second = std::min(heap[where[x]].second, w);
            heapInsert(where[x]);
        }
    }

    void dijkstra(int n, int s)
    {
        addOrUpdateOrIgnore(s, 0);
        while (heapSize > 0)
        {
            int no = heap[0].first;
            int w = heap[0].second;
            pop();
            distance[no] = w;
            for (int edge = head[no]; edge != 0; edge = next[edge])
            {
                if (distance[to[edge]] > distance[no] + weight[edge])
                {
                    addOrUpdateOrIgnore(to[edge], distance[no] + weight[edge]);
                }
            }
        }
    }

    void input()
    {
        int n{}, m{}, s{};
        std::cin >> n >> m >> s;
        int u{}, v{}, w{};
        for (int i = 0; i < m; i++)
        {
            std::cin >> u >> v >> w;
            addEdge(u, v, w);
        }

        dijkstra(n, s);

        for (int i = 1; i <= n; i++)
        {
            std::cout << distance[i] << " ";
        }
        std::cout << std::endl;
    }
}

namespace PathWithMinimumEffort
{
    class Solution
    {
    public:
        struct heapItem
        {
            int x{};
            int y{};
            int w{};
            heapItem() {}
            heapItem(int x, int y, int w) : x(x), y(y), w(w) {}
        };
        std::vector<std::vector<int>> distance;
        std::vector<heapItem> heap;
        int heapSize{};
        std::vector<std::vector<int>> where;
        int minimumEffortPath(std::vector<std::vector<int>> &heights)
        {
            int row = static_cast<int>(heights.size());
            int col = static_cast<int>(heights[0].size());
            std::vector<int> move = {-1, 0, 1, 0, -1};
            distance.assign(row, std::vector<int>(col, INT_MAX));
            heap.assign(row * col, {});
            heapSize = 0;
            where.assign(row, std::vector<int>(col, -1));
            addOrUpdateOrIgnore(0, 0, 0);
            while (heapSize > 0)
            {
                int x = heap[0].x;
                int y = heap[0].y;
                int w = heap[0].w;
                pop();
                distance[x][y] = w;
                if (x == row - 1 && y == col - 1)
                    return distance[x][y];
                for (int i = 0; i < 4; i++)
                {
                    int nx = x + move[i];
                    int ny = y + move[i + 1];
                    if (nx >= 0 && ny >= 0 && nx < row && ny < col &&
                        distance[nx][ny] > std::max(distance[x][y], std::abs(heights[nx][ny] - heights[x][y])))
                    {
                        addOrUpdateOrIgnore(nx, ny, std::max(distance[x][y], std::abs(heights[nx][ny] - heights[x][y])));
                    }
                }
            }

            return distance[row - 1][col - 1];
        }

        void heapInsert(int i)
        {
            while (i > 0 && heap[i].w < heap[(i - 1) >> 1].w)
            {
                swap(i, (i - 1) >> 1);
                i = (i - 1) >> 1;
            }
        }

        void heapify(int i)
        {
            int l = (i << 1) + 1;
            while (l < heapSize)
            {
                int best = l + 1 < heapSize && heap[l + 1].w < heap[l].w ? l + 1 : l;
                best = heap[best].w < heap[i].w ? best : i;
                if (i == best)
                    break;

                swap(i, best);
                i = best;
                l = (i << 1) + 1;
            }
        }

        void swap(int a, int b)
        {
            where[heap[a].x][heap[a].y] = b;
            where[heap[b].x][heap[b].y] = a;

            auto temp = heap[a];
            heap[a] = heap[b];
            heap[b] = temp;
        }

        void pop()
        {
            int x = heap[0].x;
            int y = heap[0].y;
            swap(0, --heapSize);
            heapify(0);
            where[x][y] = -2;
        }

        void addOrUpdateOrIgnore(int x, int y, int w)
        {
            if (where[x][y] == -1)
            {
                heap[heapSize].x = x;
                heap[heapSize].y = y;
                heap[heapSize].w = w;
                where[x][y] = heapSize++;
                heapInsert(where[x][y]);
            }
            else if (where[x][y] >= 0)
            {
                heap[where[x][y]].w = std::min(heap[where[x][y]].w, w);
                heapInsert(where[x][y]);
            }
        }
    };
}

namespace SwimInRisingWater
{
    class Solution
    {
    public:
        struct heapItem
        {
            int x{};
            int y{};
            int w{};
            heapItem() {}
            heapItem(int nx, int ny, int nw) : x(nx), y(ny), w(nw) {}
        };

        int swimInWater(std::vector<std::vector<int>> &grid)
        {
            int row = static_cast<int>(grid.size()), col = static_cast<int>(grid[0].size());
            std::vector<int> move = {-1, 0, 1, 0, -1};
            std::vector<std::vector<int>> distance(row, std::vector<int>(col, INT_MAX));
            std::vector<std::vector<bool>> visit(row, std::vector<bool>(col, false));
            auto cmp = [](const heapItem &h1, const heapItem &h2)
            { return h1.w > h2.w; };
            std::priority_queue<heapItem, std::vector<heapItem>, decltype(cmp)> heap(cmp);

            heap.emplace(0, 0, grid[0][0]);
            while (!heap.empty())
            {
                int x = heap.top().x;
                int y = heap.top().y;
                int w = heap.top().w;
                heap.pop();
                if (visit[x][y])
                    continue;
                visit[x][y] = true;
                distance[x][y] = w;
                if (x == row - 1 && y == col - 1)
                    return distance[x][y];

                for (int i = 0, nx{}, ny{}, nw{}; i < 4; i++)
                {
                    nx = x + move[i];
                    ny = y + move[i + 1];
                    if (nx >= 0 && ny >= 0 && nx < row && ny < col && !visit[nx][ny])
                    {
                        nw = std::max(w, grid[nx][ny]);
                        if (nw < distance[nx][ny])
                        {
                            heap.emplace(nx, ny, nw);
                        }
                    }
                }
            }

            return -1;
        }
    };
}

namespace ShortestPathToGetAllKeys
{
    class Solution
    {
    public:
        struct queueItem
        {
            int x{};
            int y{};
            int status{};

            queueItem() {}
            queueItem(int nx, int ny, int ns) : x(nx), y(ny), status(ns) {}
        };
        int shortestPathAllKeys(std::vector<std::string> &grid)
        {
            int n = static_cast<int>(grid.size());
            int m = static_cast<int>(grid[0].size());
            std::vector<int> move = {-1, 0, 1, 0, -1};
            std::vector<queueItem> queue(n * m * (1 << 6));
            int l{}, r{};
            std::vector<std::vector<std::vector<bool>>> visit(n, std::vector<std::vector<bool>>(m, std::vector<bool>(1 << 6, false)));
            int key{};
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    if (grid[i][j] == '@')
                    {
                        queue[r++] = {i, j, 0};
                        visit[i][j][0] = true;
                    }

                    if(grid[i][j] >= 'a' && grid[i][j] <= 'f'){
                        key |= (1 << (grid[i][j] - 'a'));
                    }
                }
            }

            int level{};

            while (l < r)
            {
                for (int k = 0, size = r - l; k < size; k++)
                {
                    int x = queue[l].x;
                    int y = queue[l].y;
                    int status = queue[l++].status;
                    
                    for (int i = 0; i < 4; i++)
                    {
                        int newStatus = status;
                        int nx = x + move[i];
                        int ny = y + move[i + 1];
                        if (nx < 0 || nx >= n || ny < 0 || ny >= m || grid[nx][ny] == '#')
                        {
                            continue;
                        }

                        if (grid[nx][ny] >= 'A' && grid[nx][ny] <= 'F' && (status & (1 << (grid[nx][ny] - 'A'))) == 0)
                        {
                            continue;
                        }

                        if (grid[nx][ny] >= 'a' && grid[nx][ny] <= 'f')
                        {
                            newStatus |= (1 << (grid[nx][ny] - 'a'));
                        }

                        if (newStatus == key)
                        {
                            return level + 1;
                        }

                        if (!visit[nx][ny][newStatus])
                        {
                            queue[r].x = nx;
                            queue[r].y = ny;
                            queue[r++].status = newStatus;
                            visit[nx][ny][newStatus] = true;
                        }
                    }
                }
                level++;
            }

            return -1;
        }
    };
}

namespace DFPeFJ{
class Solution {
public:
    struct HeapItem{
        int cur{};
        int power{};
        int cost{};
        HeapItem(){}
        HeapItem(int cu, int p, int co) : cur(cu), power(p), cost(co){}
    };
    int electricCarPlan(std::vector<std::vector<int>>& paths, int cnt, int start, int end, std::vector<int>& charge) {
        int n = static_cast<int>(charge.size());
        std::vector<std::vector<int>> distance(n, std::vector<int>(cnt + 1, INT_MAX));
        std::vector<std::vector<bool>> visit(n, std::vector<bool>(cnt + 1, false));
        std::vector<std::vector<std::pair<int, int>>> graph(n);
        for(auto& path : paths){
            graph[path[0]].push_back({path[1], path[2]});
            graph[path[1]].push_back({path[0], path[2]});
        }
        auto cmp = [](const HeapItem& h1, const HeapItem& h2){return h1.cost > h2.cost;};
        std::priority_queue<HeapItem, std::vector<HeapItem>, decltype(cmp)> heap(cmp);
        heap.emplace(start, 0, 0);

        while(!heap.empty()){
            int node = heap.top().cur;
            int power = heap.top().power;
            int cost = heap.top().cost;
            heap.pop();
            if(visit[node][power])continue;
            if(node == end)return cost;

            distance[node][power] = cost;
            visit[node][power] = true;

            if(power < cnt){
                if(!visit[node][power + 1] && cost + charge[node] < distance[node][power + 1]){
                    distance[node][power + 1] = cost + charge[node];
                    heap.emplace(node, power + 1, cost + charge[node]);
                }
            }

            for(auto& edge : graph[node]){
                if(power >= edge.second && !visit[edge.first][power - edge.second] && cost + edge.second < distance[edge.first][power - edge.second]){
                    distance[edge.first][power - edge.second] = cost + edge.second;
                    heap.emplace(edge.first, power - edge.second, cost + edge.second);
                }
            }
        }

        return -1;
    }
};
}

namespace P4568{
    #define MAXN 10001
    #define MAXM 100002
    #define MAXK 11
    std::vector<std::vector<int>> distance(MAXN, std::vector<int>(MAXK, INT_MAX));
    std::vector<std::vector<bool>> visit(MAXN, std::vector<bool>(MAXK, false));
    std::vector<int> head(MAXN, 0);
    std::vector<int> next(MAXM, 0);
    std::vector<int> to(MAXM, 0);
    std::vector<int> weight(MAXM, 0);
    int cnt = 1;
    int k{};

    struct heapItem{
        int node{};
        int free{};
        int cost{};
        heapItem(){}
        heapItem(int n, int f, int c) : node(n), free(f), cost(c) {}
    };

    void addEdge(int from, int t, int wei){
        next[cnt] = head[from];
        to[cnt] = t;
        weight[cnt] = wei;
        head[from] = cnt++;
    }
    
    void input(){
        int n{}, m{};
        std::cin >> n >> m >> k;
        int s{}, t{};
        std::cin >> s >> t;
        int a{}, b{}, c{};
        for(int i = 0;i < m;i++){
            std::cin >> a >> b >> c;
            addEdge(a + 1, b + 1, c);
            addEdge(b + 1, a + 1, c);
        }
        auto cmp = [](const heapItem& h1, const heapItem& h2){return h1.cost > h2.cost;};
        std::priority_queue<heapItem, std::vector<heapItem>, decltype(cmp)> heap(cmp);
        heap.emplace(s + 1, k, 0);
        while(!heap.empty()){
            int node = heap.top().node;
            int free = heap.top().free;
            int cost = heap.top().cost;
            heap.pop();
            if(visit[node][free])continue;
            if(node == t + 1){
                std::cout << cost << std::endl;
                return;
            }
            visit[node][free] = true;
            for(int edge = head[node];edge != 0;edge = next[edge]){
                int nextNode = to[edge];
                int nextCost = weight[edge];
                if(free > 0 && !visit[nextNode][free - 1] && cost < distance[nextNode][free - 1]){
                    distance[nextNode][free - 1] = cost;
                    heap.emplace(nextNode, free - 1, cost);
                }

                if(!visit[nextNode][free] && cost + nextCost < distance[nextNode][free]){
                    distance[nextNode][free] = cost + nextCost;
                    heap.emplace(nextNode, free, cost + nextCost);
                }
            }
        }

        std::cout << -1 << std::endl;
    }
}

int main()
{
}