/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

 void levelTraverse (struct TreeNode* node1, struct TreeNode* node2, int level) {
        if (node1 == NULL || node2 == NULL)
            return;
        
        if (level % 2 == 0) {
            int val = node1 -> val;
            node1 -> val = node2 -> val;
            node2 -> val = val;
        }

    levelTraverse (node1 -> left, node2 -> right, level + 1);
    levelTraverse (node1 -> right, node2 -> left, level + 1);
}

struct TreeNode* reverseOddLevels (struct TreeNode* root) {
    levelTraverse (root -> left, root -> right, 0);
    return root;
}