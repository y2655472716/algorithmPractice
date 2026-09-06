#include <iostream>
#include <vector>

namespace CourseSchedule{
class Solution {
public:

    std::vector<int> findOrder(int numCourses, std::vector<std::vector<int>>& prerequisites) {
        std::vector<std::vector<int>> graph(numCourses);
        std::vector<int> indgree(numCourses);
        for(auto& edge : prerequisites){
            graph[edge[1]].push_back(edge[0]);
            indgree[edge[0]]++;
        }
        std::vector<int> queue(numCourses, 0);
        int front{}, end{};
        std::vector<int> ans(numCourses);
        for(int i = 0;i < indgree.size();i++){
            if(indgree[i] == 0)queue[end++] = i;
        }
        int ans_size{};
        while(front != end){
            for(auto& to : graph[queue[front]]){
                indgree[to]--;
                if(indgree[to] == 0)queue[end++] = to;
            }

            ans[ans_size++] = queue[front++];
        }

        return ans_size == numCourses ? ans : std::vector<int>();
        
    }
};
}

namespace Classic{
    #define CMAX 200001
    std::vector<int> head(CMAX, 0);
    std::vector<int> next(CMAX, 0);
    std::vector<int> to(CMAX, 0);
    std::vector<int> queue(CMAX, 0);
    std::vector<int> ans(CMAX, 0);
    std::vector<int> indegree(CMAX, 0);
    int front{}, end{};
    int ans_size{};
    int cnt = 1;

    void addEdge(int s ,int e){
            next[cnt] = head[s];
            to[cnt] = e;
            head[s] = cnt++;
            indegree[e]++;
    }

    void input(){
        int n{}, m{};
        std::cin >> n >> m;
        int u{}, v{};
        for(int i = 0;i < m;i++){
            std::cin >> u >> v;
            addEdge(u, v);
        }

        for(int i = 1;i <= n;i++){
            if(indegree[i] == 0){
                queue[end++] = i;
            }
        }

        while(front != end){
            
            int edge = head[queue[front]];
            while(edge != 0){
                if(--indegree[to[edge]] == 0){
                    queue[end++] = to[edge]; 
                }
                edge = next[edge];
            }
            ans[ans_size++] = queue[front++];
        }
        if(ans_size != n){
            std::cout << -1 << std::endl;
        }else{
            for(int i = 0;i < ans_size;i++){
                std::cout << ans[i] << (i == ans_size - 1 ? "" : " ");
            }
        }
    }
}

namespace U107394{
    #define UMAX 100001
    std::vector<int> heap(UMAX, 0);
    int heap_size{};
    void swap(int a, int b){
        int temp = heap[a];
        heap[a] = heap[b];
        heap[b] = temp;
    }

    void heapfy(int start){
        int l = start * 2 + 1;
        while(l < heap_size){
            int best = l + 1 < heap_size && heap[l] > heap[l + 1] ? l + 1 : l;
            best = heap[best] < heap[start] ? best : start;
            if(best == start)break;

            swap(start, best);
            start = best;
            l = start * 2 + 1;
        }
        
    }

    void push(int n){
        int cur = heap_size++;
        heap[cur] = n;
        int up = (cur - 1) / 2;
        while(cur > 0){
            if(heap[up] > heap[cur]){
                swap(up, cur);
                cur = up;
                up = (cur - 1) / 2;
            }else{break;}
        }
    }

    void pop(){
        swap(0, --heap_size);
        heapfy(0);
    }



    std::vector<int> head(UMAX, 0);
    std::vector<int> next(UMAX, 0);
    std::vector<int> to(UMAX, 0);
    std::vector<int> indegree(UMAX, 0);
    std::vector<int> ans(UMAX, 0);
    int ans_size{}, cnt = 1;

    void addEdge(int s, int e){
        next[cnt] = head[s];
        to[cnt] = e;
        indegree[e]++;
        head[s] = cnt++;
    }

    void input(){
        int n{}, m{};
        std::cin >> n >> m;
        int u{}, v{};
        for(int i = 0;i < m;i++){
            std::cin >> u >> v;
            addEdge(u, v);
        }

        for(int i = 1;i <= n;i++){
            if(indegree[i] == 0)push(i);
        }

        while(heap_size > 0){
            int cur = heap[0];
            pop();
            ans[ans_size++] = cur;
            int edge = head[cur];
            while(edge != 0){
                if(--indegree[to[edge]] == 0){
                    push(to[edge]);
                }
                edge = next[edge];
            }   
        }
        if(ans_size != n)return;
        for(int i = 0;i < ans_size;i++){
            std::cout << ans[i] << " ";
        }
    }
}

namespace Jf1JuT{
class Solution {
public:
    std::string alienOrder(std::vector<std::string>& words) {
        std::vector<int> w(26, -1);
        for(auto& word : words){
            for(auto& c : word){
                w[c - 'a'] = 0;
            }
        }

        std::vector<std::vector<int>> graph(26);
        for(int i = 0;i < words.size() - 1;i++){
            std::string cur = words[i];
            std::string next = words[i + 1];
            int len = std::min(cur.size(), next.size());
            int j{};
            for(;j < len;j++){
                if(cur[j] != next[j]){
                    graph[cur[j] - 'a'].push_back(next[j] - 'a');
                    w[next[j] - 'a']++;
                    break;
                }
            }
            if(j < cur.size() && j == next.size())return "";
        }
        std::vector<int> queue(26);
        int front{}, end{};
        int kind{};
        for(int i = 0;i < 26;i++){
            if(w[i] != -1)kind++;
            if(w[i] == 0){
                queue[end++] = i;
            }
        }
        
        std::string ans;
        while(front != end){
            for(auto& next : graph[queue[front]]){
                if(--w[next] == 0){
                    queue[end++] = next;
                }
            }
            ans += queue[front++] + 'a';
        }

        return ans.size() == kind ? ans : "";
    }
};
}

namespace StampingTheSequence{
class Solution {
public:
    std::vector<int> movesToStamp(std::string stamp, std::string target) {
        int m = static_cast<int>(stamp.size());
        int n = static_cast<int>(target.size());
        std::vector<int> queue(n - m + 1);
        int front{}, end{};
        std::vector<int> indegree(n, m);
        std::vector<std::vector<int>> graph(n);

        for(int i = 0;i < n - m + 1;i++){
            for(int j = i, k = 0;k < m;k++, j++){
                if(target[j] == stamp[k]){
                    indegree[i]--;
                }else{
                    graph[j].push_back(i);
                }
            }
            if(indegree[i] == 0){
                queue[end++] = i;
            }
        }
        std::vector<int> ans;
        std::vector<bool> visit(n, false);
        while(front != end){
            int cur = queue[front++];
            ans.push_back(cur);
            for(int i = cur;i < cur + m;i++){
                if(!visit[i]){
                    visit[i] = true;
                    for(auto to : graph[i]){
                        if(--indegree[to] == 0){
                            queue[end++] = to;
                        }
                    }
                }
            }
        }

        if(ans.size() != n - m + 1){
            return {};
        }

        for(int l = 0, r = ans.size() - 1;l < r;l++, r--){
            int temp = ans[l];
            ans[l] = ans[r];
            ans[r] = temp;
        }

        return ans;
}
};
}

namespace MaxFoodChain{
    #define MNMAX 5001
    #define MEMAX 500001
    #define MMOD  80112002

    std::vector<int> head(MNMAX, 0);
    std::vector<int> next(MEMAX, 0);
    std::vector<int> to(MEMAX, 0);
    std::vector<int> indegree(MNMAX, 0);
    int cnt = 1;

    std::vector<int> queue(MNMAX, 0);
    int front{}, end{};
    std::vector<int> nums(MNMAX, 0);

    void addEdge(int f, int t){
        next[cnt] = head[f];
        to[cnt] = t;
        head[f] = cnt++;
        indegree[t]++;
    }

    void input(){
        int n{}, m{};
        std::cin >> n >> m;
        int A{}, B{};
        for(int i = 0;i < m;i++){
            std::cin >> A >> B;
            addEdge(A, B);
        }
        for(int i = 1;i <= n;i++){
            if(indegree[i] == 0){
                queue[end++] = i;
                nums[i] = 1;
            }
        }
        int ans{};
        while(front < end){
            int cur = queue[front++];
            int edge = head[cur];
            if(edge == 0){
                ans = (nums[cur] + ans) % MMOD;
            }
            while(edge != 0){
                nums[to[edge]] = (nums[to[edge]] + nums[cur]) % MMOD;
                if(--indegree[to[edge]] == 0){
                    queue[end++] = to[edge];
                }
                edge = next[edge];
            }
        }

        std::cout << ans << std::endl;
    }
}

namespace LoudAndRich{
class Solution {
public:
    std::vector<int> loudAndRich(std::vector<std::vector<int>>& richer, std::vector<int>& quiet) {
        int n = static_cast<int>(quiet.size());
        std::vector<std::vector<int>> graph(n);
        std::vector<int> indegree(n, 0);
        for(auto& edge : richer){
            graph[edge[0]].push_back(edge[1]);
            indegree[edge[1]]++;
        }
        std::vector<int> queue(n, 0);
        int front{}, end{};
        std::vector<int> people(n);
        for(int i = 0;i < n;i++){
            people[i] = i;
        }
        for(int i = 0;i < n;i++){
            if(indegree[i] == 0){
                queue[end++] = i;
            }
        }

        while(front < end){
            int cur = queue[front++];
            for(auto& to : graph[cur]){
                if(quiet[people[to]] > quiet[people[cur]]){
                    people[to] = people[cur];
                }
                if(--indegree[to] == 0){
                    queue[end++] = to;
                }
            }
        }

        return people;
    }
};
}

namespace ParallelCourses{
class Solution {
public:
    int minimumTime(int n, std::vector<std::vector<int>>& relations, std::vector<int>& time) {
        std::vector<std::vector<int>> graph(n + 1);
        std::vector<int> indegree(n + 1, 0);
        for(auto& relation : relations){
            graph[relation[0]].push_back(relation[1]);
            indegree[relation[1]]++;
        }
        std::vector<int> completeTime(n + 1, 0);
        std::vector<int> queue(n + 1, 0);
        int front{}, end{};
        for(int i = 1;i <= n;i++){
            if(indegree[i] == 0){
                queue[end++] = i;
            }
        }
        int ans{};
        while(front < end){
            int cur = queue[front++];
            completeTime[cur] += time[cur - 1];
            ans = std::max(completeTime[cur], ans);
            for(auto& next : graph[cur]){
                completeTime[next] = std::max(completeTime[cur], completeTime[next]);
                if(--indegree[next] == 0){
                    queue[end++] = next;
                }
            }
        }
        return ans;
    }
};
}

namespace MaximumEmployeesToBeInvitedToAMeeting{
class Solution {
public:
    int maximumInvitations(std::vector<int>& favorite) {
        int n = static_cast<int>(favorite.size());
        std::vector<int> indegree(n);
        for(auto& f : favorite){
            indegree[f]++;
        }

        std::vector<int> deep(n, 0);
        std::vector<int> queue(n);
        int front{}, end{};
        for(int i = 0;i < n;i++){
            if(indegree[i] == 0)queue[end++] = i;
        }

        while(front != end){
            int cur = queue[front++];
            int to = favorite[cur];
            deep[to] = std::max(deep[to], deep[cur] + 1);
            if(--indegree[to] == 0){
                queue[end++] = to;
            }
        }

        int smallSize{};
        int bigSize{};
        for(int i = 0;i < n;i++){
            if(indegree[i] != 0){
                int curSize = 1;
                indegree[i] = 0;
                for(int j = favorite[i];j != i;curSize++){
                    indegree[j] = 0;
                    j = favorite[j];
                }

                if(curSize == 2){
                    smallSize += deep[i] + deep[favorite[i]] + 2;
                }else{
                    bigSize = std::max(bigSize, curSize);
                }
            }
        }

        return std::max(smallSize, bigSize);
    }
};
}

int main(){

}