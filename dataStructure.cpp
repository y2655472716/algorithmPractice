#include <iostream>
#include <unordered_map>
#include <memory>
#include <vector>
#include <random>
#include <unordered_set>

namespace SetAll
{
    class HashMap
    {

        struct KV
        {
            int value{};
            int time{};
            KV() {}
            KV(int v, int t) : value(v), time(t) {}
        };

        int setAllValue{};
        int setAllTime = -1;
        int cnt{};
        std::unordered_map<int, KV> map;

    public:
        HashMap()
        {
            map.clear();
            setAllValue = 0;
            setAllTime = -1;
            cnt = 0;
        }

        void put(int x, int y)
        {
            map[x] = KV(y, cnt++);
        }

        int get(int x)
        {
            if (map.find(x) == map.end())
                return -1;
            KV val = map[x];
            if (setAllTime >= val.time)
                return setAllValue;
            else
                return val.value;
        }

        void setAll(int value)
        {
            setAllValue = value;
            setAllTime = cnt++;
        }
    };

    void input()
    {
        int N{};
        std::cin >> N;
        HashMap hmap;
        int opt{}, x{}, y{};
        while (N-- > 0)
        {
            std::cin >> opt;
            switch (opt)
            {
            case 1:
            {
                std::cin >> x >> y;
                hmap.put(x, y);
                break;
            }
            case 2:
            {
                std::cin >> x;
                std::cout << hmap.get(x) << std::endl;
                break;
            }
            case 3:
            {
                std::cin >> x;
                hmap.setAll(x);
                break;
            }
            default:
                break;
            }
        }
    }
}

namespace LRU
{
    class LRUCache
    {
        struct ListNode
        {
            int key{};
            int val{};
            std::weak_ptr<ListNode> pre;
            std::shared_ptr<ListNode> next;

            ListNode(int k, int v) : key(k), val(v) {}
        };
        class DoubleList
        {
            std::shared_ptr<ListNode> head;
            std::shared_ptr<ListNode> tail;

        public:
            DoubleList()
            {
                head = std::make_shared<ListNode>(-1, -1);
                tail = std::make_shared<ListNode>(-1, -1);
                head->next = tail;
                tail->pre = head;
            }

            void putTail(std::shared_ptr<ListNode> node)
            {
                if (!node)
                    return;
                tail->pre.lock()->next = node;
                node->pre = tail->pre;
                node->next = tail;
                tail->pre = node;
            }

            int removeHead()
            {
                if (head->next == tail)
                    return -1;

                auto node = head->next;
                int key = node->key;
                head->next = node->next;
                node->next->pre = head;
                node->next = nullptr;
                node->pre.reset();
                return key;
            }

            void moveToTail(std::shared_ptr<ListNode> node)
            {
                if (!node)
                    return;

                node->pre.lock()->next = node->next;
                node->next->pre = node->pre;

                putTail(node);
            }
        };
        int capacity{};
        int size{};

        DoubleList list;
        std::unordered_map<int, std::shared_ptr<ListNode>> map;

    public:
        LRUCache(int capacity)
        {
            this->capacity = capacity;
            size = 0;
        }

        int get(int key)
        {
            if (map.find(key) == map.end())
                return -1;

            auto node = map[key];
            list.moveToTail(node);
            return node->val;
        }

        void put(int key, int value)
        {
            if (map.find(key) != map.end())
            {
                auto node = map[key];
                node->val = value;
                list.moveToTail(node);
            }
            else
            {
                auto node = std::make_shared<ListNode>(key, value);
                if (size < capacity)
                {
                    list.putTail(node);
                    size++;
                    map[key] = node;
                }
                else
                {
                    int removeKey = list.removeHead();
                    map.erase(removeKey);

                    list.putTail(node);
                    map[key] = node;
                }
            }
        }
    };
}

namespace RandomizedSet
{
    class RandomizedSet
    {
        std::unordered_map<int, int> map;
        std::vector<int> value;

    public:
        RandomizedSet()
        {
        }

        bool insert(int val)
        {
            if (map.find(val) != map.end())
            {
                return false;
            }
            map[val] = map.size();
            value.push_back(val);
            return true;
        }

        bool remove(int val)
        {
            if (map.find(val) == map.end())
            {
                return false;
            }

            int index = map[val];
            int lastValue = value.back();
            value[index] = lastValue;
            map[lastValue] = index;
            map.erase(val);
            value.pop_back();
            return true;
        }

        int getRandom()
        {
            if (map.empty())
                return INT_MIN;
            std::random_device rd;
            std::mt19937 gen(rd());

            std::uniform_int_distribution<int> dist(0, (map.size() - 1));
            return value[dist(gen)];
        }
    };

}

namespace RandomizedCollection
{
    class RandomizedCollection
    {
        std::unordered_map<int, std::unordered_set<int>> map;
        std::vector<int> values;

    public:
        RandomizedCollection()
        {
        }

        bool insert(int val)
        {
            int index = values.size();
            values.push_back(val);
            if (map.find(val) == map.end())
            {
                map[val] = std::unordered_set<int>();
                map[val].insert(index);
                return true;
            }
            else
            {
                map[val].insert(index);
                return false;
            }
        }

        bool remove(int val)
        {
            if (map.find(val) == map.end())
                return false;
            int index = *map[val].begin();
            int lastIndex = values.size() - 1;
            int tempValue = values.back();
            values[index] = tempValue;
            map[val].erase(index);
            if (index != lastIndex)
            {
                map[tempValue].insert(index);
                map[tempValue].erase(lastIndex);
            }

            values.pop_back();
            if (map[val].empty())
            {
                map.erase(val);
            }
            return true;
        }

        int getRandom()
        {
            if (values.empty())
                return -1;

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> dist(0, values.size() - 1);

            return values[dist(gen)];
        }
    };
}

int main()
{
    RandomizedSet::RandomizedSet set;
    std::cout << set.remove(0) << std::endl;
    std::cout << set.remove(0) << std::endl;
    std::cout << set.insert(0) << std::endl;
    std::cout << set.getRandom() << std::endl;
    std::cout << set.remove(0) << std::endl;
    std::cout << set.insert(0) << std::endl;
}