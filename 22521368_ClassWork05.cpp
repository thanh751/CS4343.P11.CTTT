//Name: Trần Tịnh Đan Thanh
//Student's ID: 22521368
//Classwork 05
#include <bits/stdc++.h>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int value) : val(value), left(nullptr), right(nullptr) {}
};

// Binary Tree class
class BinaryTree {
public:
    TreeNode* root;

    BinaryTree() : root(nullptr) {}

    // Insert value
    void insert(int val) {
        root = insertRec(root, val);
    }

    TreeNode* insertRec(TreeNode* node, int val){
        if(!node){
            return new TreeNode(val);
        }
        if(val < node->val){
            node->left = insertRec(node->left, val);
        }
        else{
            node->right = insertRec(node->right, val);
        }
        return node;
    }

    // Search value
    TreeNode* search(int val){
        return searchRec(root, val);
    }

    TreeNode* searchRec(TreeNode* node, int val){
        if(!node || node->val == val){
            return node;
        }
        if(val < node->val){
            return searchRec(node->left, val);
        }
        else{
            return searchRec(node->right, val);
        }
    }

    // Delete value
    TreeNode* deleteNode(TreeNode* root, int key){
        if(!root) return root;
        if(key < root->val){
            root->left = deleteNode(root->left, key);
        }
        else if(key > root->val){
            root->right = deleteNode(root->right, key);
        }
        else{
            if(!root->left){
                TreeNode* temp = root->right;
                delete root;
                return temp;
            }
            else if(!root->right){
                TreeNode* temp = root->left;
                delete root;
                return temp;
            }
            TreeNode* temp = minValueNode(root->right);
            root->val = temp->val;
            root->right = deleteNode(root->right, temp->val);
        }
        return root;
    }

    TreeNode* minValueNode(TreeNode* node){
        TreeNode* current = node;
        while(current && current->left)
            current = current->left;
        return current;
    }

    // Pre-order traversal
    void preorder(TreeNode* node, vector<int>& res){
        if(node){
            res.push_back(node->val);
            preorder(node->left, res);
            preorder(node->right, res);
        }
    }

    // In-order traversal
    void inorder(TreeNode* node, vector<int>& res){
        if(node){
            inorder(node->left, res);
            res.push_back(node->val);
            inorder(node->right, res);
        }
    }

    // Post-order traversal
    void postorder(TreeNode* node, vector<int>& res){
        if(node){
            postorder(node->left, res);
            postorder(node->right, res);
            res.push_back(node->val);
        }
    }

    // Level-order traversal
    vector<vector<int>> levelOrder(){
        vector<vector<int>> levels;
        if(!root) return levels;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            int size = q.size();
            vector<int> level;
            for(int i=0;i<size;i++){
                TreeNode* node = q.front(); q.pop();
                level.push_back(node->val);
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
            levels.push_back(level);
        }
        return levels;
    }

    // Calculate height
    int height(TreeNode* node){
        if(!node) return 0;
        return 1 + max(height(node->left), height(node->right));
    }

    // Check if balanced
    bool isBalanced(TreeNode* node){
        if(!node) return true;
        int lh = height(node->left);
        int rh = height(node->right);
        if(abs(lh - rh) > 1) return false;
        return isBalanced(node->left) && isBalanced(node->right);
    }

    // Diameter of tree
    int diameter(TreeNode* node, int &dia){
        if(!node) return 0;
        int lh = diameter(node->left, dia);
        int rh = diameter(node->right, dia);
        dia = max(dia, lh + rh);
        return 1 + max(lh, rh);
    }

    // Lowest Common Ancestor
    TreeNode* LCA(TreeNode* node, int n1, int n2){
        if(!node) return nullptr;
        if(node->val > n1 && node->val > n2)
            return LCA(node->left, n1, n2);
        if(node->val < n1 && node->val < n2)
            return LCA(node->right, n1, n2);
        return node;
    }

    // Maximum Path Sum
    int maxPathSumUtil(TreeNode* node, int &res){
        if(!node) return 0;
        int left = max(maxPathSumUtil(node->left, res), 0);
        int right = max(maxPathSumUtil(node->right, res), 0);
        res = max(res, left + right + node->val);
        return max(left, right) + node->val;
    }

    int maxPathSum(){
        int res = INT_MIN;
        maxPathSumUtil(root, res);
        return res;
    }

    // Reconstruct tree from inorder and postorder
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder){
        int n = inorder.size();
        unordered_map<int, int> idx_map;
        for(int i=0;i<n;i++) idx_map[inorder[i]] = i;
        return build(inorder, postorder, 0, n-1, 0, n-1, idx_map);
    }

    TreeNode* build(vector<int>& inorder, vector<int>& postorder, int inStart, int inEnd, int postStart, int postEnd, unordered_map<int, int>& idx_map){
        if(inStart > inEnd || postStart > postEnd) return nullptr;
        int rootVal = postorder[postEnd];
        TreeNode* root = new TreeNode(rootVal);
        int inRoot = idx_map[rootVal];
        int numsLeft = inRoot - inStart;
        root->left = build(inorder, postorder, inStart, inRoot-1, postStart, postStart+numsLeft-1, idx_map);
        root->right = build(inorder, postorder, inRoot+1, inEnd, postStart+numsLeft, postEnd-1, idx_map);
        return root;
    }

    // Vertical Order Traversal
    vector<vector<int>> verticalOrder(){
        map<int, vector<int>> m;
        queue<pair<TreeNode*, int>> q;
        vector<vector<int>> res;
        if(!root) return res;
        q.push({root, 0});
        while(!q.empty()){
            auto p = q.front(); q.pop();
            TreeNode* node = p.first;
            int hd = p.second;
            m[hd].push_back(node->val);
            if(node->left) q.push({node->left, hd-1});
            if(node->right) q.push({node->right, hd+1});
        }
        for(auto it : m){
            res.push_back(it.second);
        }
        return res;
    }

    // Merge two trees
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2){
        if(!t1) return t2;
        if(!t2) return t1;
        t1->val += t2->val;
        t1->left = mergeTrees(t1->left, t2->left);
        t1->right = mergeTrees(t1->right, t2->right);
        return t1;
    }
};

// Binary Search Tree class
class BinarySearchTree : public BinaryTree {
public:
    // Find minimum
    int findMin(){
        TreeNode* node = root;
        while(node->left) node = node->left;
        return node->val;
    }

    // Find maximum
    int findMax(){
        TreeNode* node = root;
        while(node->right) node = node->right;
        return node->val;
    }
};

int main(){
    BinarySearchTree bst;
    // Insert elements
    bst.insert(20);
    bst.insert(10);
    bst.insert(30);
    bst.insert(5);
    bst.insert(15);
    bst.insert(25);
    bst.insert(35);

    // Traversals
    vector<int> pre, in, post;
    bst.preorder(bst.root, pre);
    bst.inorder(bst.root, in);
    bst.postorder(bst.root, post);

    // Level-order
    vector<vector<int>> level = bst.levelOrder();

    // Diameter
    int dia = 0;
    bst.diameter(bst.root, dia);

    // Height
    int ht = bst.height(bst.root);

    // Check balanced
    bool balanced = bst.isBalanced(bst.root);

    // LCA
    TreeNode* lca = bst.LCA(bst.root, 5, 15);

    // Max Path Sum
    int maxSum = bst.maxPathSum();

    // Reconstruct tree
    vector<int> inorder = {5,10,15,20,25,30,35};
    vector<int> postorder = {5,15,10,25,35,30,20};
    TreeNode* newRoot = bst.buildTree(inorder, postorder);

    // Vertical Order
    vector<vector<int>> vertical = bst.verticalOrder();

    // Merge trees
    BinarySearchTree bst2;
    bst2.insert(20);
    bst2.insert(10);
    bst2.insert(30);
    bst2.insert(5);
    bst2.insert(15);
    bst2.insert(25);
    bst2.insert(35);
    TreeNode* mergedRoot = bst.mergeTrees(bst.root, bst2.root);

    return 0;
}