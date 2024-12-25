/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

void preOrder (struct TreeNode* Node, int level, int* arr, int* sz) {
    if (Node == NULL) return;
    if (*sz <= level) {
        (*sz)++;
        arr [level] = INT_MIN;
    }
    arr [level] = (arr [level] > Node -> val) ? arr [level] : Node -> val;

    preOrder (Node -> left, level + 1, arr, sz);
    preOrder (Node -> right, level + 1, arr, sz);
}

int* largestValues (struct TreeNode* root, int* returnSize) {

    if (root == NULL) {
        *returnSize = 0;
        return NULL;
    }

    int sz = 0;
    int* arr = (int*) malloc (10001 * sizeof (int));

    preOrder (root, 0, arr, &sz);

    *returnSize = sz;

    return arr;
}