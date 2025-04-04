/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode* dfs (struct TreeNode* root, int maxi, int len) {
    if (!root) return NULL;  
    if (maxi - 1 == len) return root;
    struct TreeNode* left = dfs (root -> left, maxi, len + 1);
    struct TreeNode* right = dfs (root -> right, maxi, len + 1);
    if (left && right) return root;
    return left ? left : right;
}

int maxDepth(struct TreeNode* root) {
    if (!root) return 0;
    return 1 + fmax (maxDepth (root -> left), maxDepth (root -> right));
}

struct TreeNode* lcaDeepestLeaves (struct TreeNode* root) {
    int maxi = maxDepth(root);
    return dfs (root, maxi, 0);
}