#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <unordered_map>
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
namespace BFS
{

    std::vector<TreeNode *> nodes(2001);
    int l{}, r{};
    std::vector<std::vector<int>> levelOrder(TreeNode *root)
    {
        if (!root)
            return {};
        std::vector<std::vector<int>> ans;
        nodes[r++] = root;
        int size = 1;
        std::vector<int> v;
        while (l != r)
        {
            if (size == 0)
            {
                ans.push_back(v);
                size = r - l;
                v.clear();
            }

            v.push_back(nodes[l]->val);
            size--;
            if (nodes[l]->left)
            {
                nodes[r++] = nodes[l]->left;
            }

            if (nodes[l]->right)
            {
                nodes[r++] = nodes[l]->right;
            }
            l++;
        }
        ans.push_back(v);
        return ans;
    }

    std::vector<std::vector<int>> zigzagLevelOrder(TreeNode *root)
    {
        if (!root)
            return {};
        std::vector<std::vector<int>> ans;
        std::vector<int> v;
        bool reverse = false;
        nodes[r++] = root;
        int size{};
        while (l < r)
        {
            size = r - l;

            for (int i = reverse ? r - 1 : l, j = reverse ? -1 : 1, k{}; k < size; i += j, k++)
            {
                v.push_back(nodes[i]->val);
            }

            while (size > 0)
            {
                if (nodes[l]->left)
                {
                    nodes[r++] = nodes[l]->left;
                }

                if (nodes[l]->right)
                {
                    nodes[r++] = nodes[r]->right;
                }
                size--;
                l++;
            }

            ans.push_back(v);
            v.clear();
            reverse = !reverse;
        }

        return ans;
    }

}

namespace WidthOfBinaryTree
{
    std::vector<TreeNode *> nodes(3001);
    std::vector<unsigned> ids(3001);
    int l{}, r{};

    int widthOfBinaryTree(TreeNode *root)
    {
        if (!root)
            return 0;
        nodes[r] = root;
        ids[r++] = 1;
        unsigned ans = 1;
        while (l < r)
        {
            int size = r - l;
            ans = std::max(ans, ids[r - 1] - ids[l] + 1);
            for (int i = 0; i < size; i++)
            {
                if (nodes[l]->left)
                {
                    nodes[r] = nodes[l]->left;
                    ids[r++] = ids[l] * 2;
                }

                if (nodes[l]->right)
                {
                    nodes[r] = nodes[l]->right;
                    ids[r++] = ids[l] * 2 + 1;
                }
                l++;
            }
        }

        return ans;
    }
}

namespace BinaryTreeDepth
{
    struct TreeNode
    {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };
    int maxDepth(TreeNode *root)
    {
        return !root ? 0 : std::max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }

    int minDepth(TreeNode *root)
    {
        if (!root)
        {
            return 0;
        }

        if (!root->left && !root->right)
        {
            return 1;
        }

        int ldeep = INT_MAX;
        int rdeep = INT_MAX;

        if (root->left)
        {
            ldeep = minDepth(root->left);
        }
        if (root->right)
        {
            rdeep = minDepth(root->right);
        }
        return std::min(ldeep, rdeep) + 1;
    }
}

namespace Codec1
{
    class Codec
    {
    public:
        std::string serializeProcess(TreeNode *root)
        {
            if (!root)
            {
                return "#,";
            }

            std::string ans = std::to_string(root->val) + ",";
            ans += serializeProcess(root->left);
            ans += serializeProcess(root->right);
            return ans;
        }

        std::string serialize(TreeNode *root)
        {
            return serializeProcess(root);
        }

        TreeNode *deserializeProcess(std::vector<std::string> &data, int &index)
        {
            if (index == data.size())
            {
                return nullptr;
            }
            if (data[index] == "#")
            {
                index++;
                return nullptr;
            }
            TreeNode *root = new TreeNode(std::stoi(data[index++]));
            root->left = deserializeProcess(data, index);
            root->right = deserializeProcess(data, index);

            return root;
        }

        TreeNode *deserialize(std::string data)
        {
            if (data.empty())
                return nullptr;
            std::vector<std::string> values;

            std::stringstream ss(data);
            std::string token;

            while (std::getline(ss, token, ','))
            {
                values.push_back(token);
            }
            int index = 0;
            return deserializeProcess(values, index);
        }
    };
}

namespace Codec2
{
    class Codec
    {
    public:
        std::string serialize(TreeNode *root)
        {
            std::string ans;
            std::queue<TreeNode *> queue;
            if (!root)
            {
                ans += "#,";
                return ans;
            }

            queue.push(root);
            ans += std::to_string(root->val) + ",";
            while (!queue.empty())
            {
                if (queue.front()->left)
                {
                    queue.push(queue.front()->left);
                    ans += std::to_string(queue.front()->left->val) + ",";
                }
                else
                {
                    ans += "#,";
                }

                if (queue.front()->right)
                {
                    queue.push(queue.front()->right);
                    ans += std::to_string(queue.front()->right->val) + ",";
                }
                else
                {
                    ans += "#,";
                }
                queue.pop();
            }

            return ans;
        }

        TreeNode *deserialize(std::string data)
        {
            if (data.empty())
                return nullptr;
            std::stringstream ss(data);
            std::vector<std::string> v;
            std::string item;
            while (std::getline(ss, item, ','))
            {
                v.push_back(item);
            }
            if (v[0] == "#")
                return nullptr;
            int index = 0;
            TreeNode *root = new TreeNode(std::stoi(v[index++]));
            std::queue<TreeNode *> queue;
            queue.push(root);
            while (!queue.empty())
            {
                queue.front()->left = v[index] == "#" ? nullptr : new TreeNode(std::stoi(v[index]));
                index++;
                queue.front()->right = v[index] == "#" ? nullptr : new TreeNode(std::stoi(v[index]));
                index++;
                if (queue.front()->left)
                {
                    queue.push(queue.front()->left);
                }
                if (queue.front()->right)
                {
                    queue.push(queue.front()->right);
                }
                queue.pop();
            }

            return root;
        }
    };
}

namespace BuildTree
{
    TreeNode *f(std::vector<int> &preorder, int l1, int r1,
                std::vector<int> &inorder, int l2, int r2,
                std::unordered_map<int, int>& map)
    {
        if(l1 > r1)return nullptr;

        TreeNode *head = new TreeNode(preorder[l1]);
        if(l1 == r1)return head;

        int k = map[preorder[l1]];
        head->left = f(preorder, l1 + 1, l1 + k - l2, inorder, l2, k - 1, map);
        head->right = f(preorder, l1 + k - l2 + 1, r1, inorder, k + 1, r2, map);
        return head;
    }
    TreeNode *buildTree(std::vector<int> &preorder, std::vector<int> &inorder)
    {
        if(preorder.empty() || inorder.empty())return nullptr;
        std::unordered_map<int, int> map;
        for(int i = 0;i < inorder.size();i++){
            map[inorder[i]] = i;
        }

        return f(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1, map);
    }
}

namespace CompleteTree{
    bool isCompleteTree(TreeNode* root) {
        if(!root)return true;

        std::queue<TreeNode *> queue;
        queue.push(root);
        bool leaf = false;
        while(!queue.empty()){
            if((!queue.front()->left && queue.front()->right)
        ||
                (leaf && (queue.front()->left || queue.front()->right))){
                return false;
            }

            if(queue.front()->left){
                queue.push(queue.front()->left);
            }

            if(queue.front()->right){
                queue.push(queue.front()->right);
            }
            if(!queue.front()->left || !queue.front()->right){
                leaf = true;
            }
            queue.pop();
        }
        return true;
    }
}

namespace CountNodes{

    int mostLeft(TreeNode* root, int level){
        while(root){
            level++;
            root = root->left;
        }
        return level - 1;
    }

    int f(TreeNode* root, int level, int h){
        if(level == h)return 1;

        if(mostLeft(root->right, level + 1) == h){
            return (1 << (h - level)) + f(root->right, level + 1, h);
        }else{
            return (1 << (h - level - 1)) + f(root->left, level + 1, h);
        }
    }

    int countNodes(TreeNode* root) {
        if(!root)return 0;

        return f(root, 1, mostLeft(root, 1));
    }
}

int main()
{
    // TreeNode *root = new TreeNode(1);
    // root->left = new TreeNode(2);
    // root->right = new TreeNode(3);
    // root->right->left = new TreeNode(4);
    // std::cout << Codec2::Codec().serialize(root) << std::endl;
    TreeNode *root = Codec2::Codec().deserialize("1,2,3,#,#,4,#,#,#,");
    std::cout << std::endl;
}