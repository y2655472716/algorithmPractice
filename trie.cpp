#include <iostream>
#include <vector>
#include <unordered_map>

namespace Trie1{
    struct TrieNode{
        int pass{};
        int end{};
        std::unordered_map<char, TrieNode*> nexts;
        TrieNode() = default;
        TrieNode(int pa, int en) : pass(pa), end(en){}
        ~TrieNode(){
            for(auto& pair : nexts){
                auto& node = pair.second;
                delete node;
                node = nullptr;
            }
            nexts.clear();
        }
    };
    class Trie{
        TrieNode* root{};
    public:
        
        Trie(){
            root = new TrieNode();
        }

        void _insert(const std::string& word){
            root->pass++;
            TrieNode* node = root;
            for(auto& c : word){
                if(node->nexts.find(c) == node->nexts.end()){
                    node->nexts[c] = new TrieNode();
                }
                node = node->nexts[c];
                node->pass++;
            }
            node->end++;
        }

        bool _search(const std::string& word){
            if(root->pass == 0)return false;
            TrieNode* node = root;
            for(auto& c : word){
                if(node->nexts.find(c) == node->nexts.end()){
                    return false;
                }
                node = node->nexts[c];
            }

            return node->end > 0;
        }

        void _delete(const std::string& word){
            if(!_search(word)){return;}
            root->pass--;
            TrieNode* node = root;
            for(auto& c : word){
                if(--node->nexts[c]->pass == 0){
                    delete node->nexts[c];
                    node->nexts[c] = nullptr;
                    node->nexts.erase(c);
                    return;
                }

                node = node->nexts[c];
            }
            node->end--;
        }

        int _prefixNumber(const std::string& pre){
            TrieNode* node = root;
            for(auto& c : pre){
                if(node->nexts.find(c) == node->nexts.end()){
                    return 0;
                }

                node = node->nexts[c];
            }

            return node->pass;
        }
    };

    void input(){
        int m{};
        std::cin >> m;
        Trie tree;
        while(m-- > 0){
            int op{};
            std::string s{};
            std::cin >> op >> s;
            switch (op)
            {
            case 1:
                tree._insert(s);
                break;
            case 2:
                tree._delete(s);
                break;
            case 3:
                std::cout << (tree._search(s) ? "YES" : "NO") << std::endl;
                break;
            default:
                std::cout << tree._prefixNumber(s) << std::endl;
                break;
            }
        }
    }
}

namespace Trie2{
    #define T_MAX 200000
    #define CHARACTER 26
    std::vector<std::vector<int>> trie(T_MAX, std::vector<int>(CHARACTER));
    std::vector<int> pass(T_MAX);
    std::vector<int> end(T_MAX);

    class Trie{
        int cnt = 1;
        int root = 1;
    public:
        Trie(){
            cnt = 1;
        }

        ~Trie(){
            trie.clear();
            pass.clear();
            end.clear();
        }

        void _insert(const std::string& word){
            pass[root]++;
            int node = root;
            int path{};
            for(auto& c : word){
                path = c - 'a';
                if(trie[node][path] == 0){
                    trie[node][path] = ++cnt;
                }
                node = trie[node][path];
                pass[node]++;
            }

            end[node]++;
        }

        bool _search(const std::string& word){
            if(pass[root] == 0)return false;
            int node = root;
            int path{};
            for(auto& c : word){
                path = c - 'a';
                if(trie[node][path] == 0){
                    return false;
                }

                node = trie[node][path];
            }
            return end[node] > 0;
        }

        void _delete(const std::string& word){
            if(!_search(word)){return;}
            pass[root]--;
            int node = root;
            int path{};
            for(auto& c : word){
                path = c - 'a';
                if(--pass[trie[node][path]] == 0){
                    trie[node][path] = 0;
                    return;
                }
                node = trie[node][path];
            }

            end[node]--;
        }

        int _prefixNumber(const std::string& pre){
            int node = root;
            int path{};
            for(auto& c : pre){
                path = c - 'a';
                if(trie[node][path] == 0)return 0;
                node = trie[node][path];
            }

            return pass[node];
        }
    };

    void input(){
        int m{};
        std::cin >> m;
        Trie tree;
        while(m-- > 0){
            int op{};
            std::string s{};
            std::cin >> op >> s;
            switch (op)
            {
            case 1:
                tree._insert(s);
                break;
            case 2:
                tree._delete(s);
                break;
            case 3:
                std::cout << (tree._search(s) ? "YES" : "NO") << std::endl;
                break;
            default:
                std::cout << tree._prefixNumber(s) << std::endl;
                break;
            }
        }
    }

}

int main(){
    Trie2::input();
}