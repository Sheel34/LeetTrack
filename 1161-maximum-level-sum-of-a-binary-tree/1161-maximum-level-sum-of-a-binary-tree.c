/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int maxLevelSum (struct TreeNode* root) {
    if (root == NULL) return 0;
    struct TreeNode** queue = (struct TreeNode**) malloc (sizeof (struct TreeNode*) * 10001);
    int front = 0, rear = 0;
    queue [rear++] = root;
    int level = 1;
    int maxSum = INT_MIN;
    int maxLevel = 1;
    while (front < rear) {
        int size = rear - front;
        int levelSum = 0;
        for (int i = 0; i < size; i++) {
            struct TreeNode* node = queue [front++];
            levelSum += node -> val;
            if (node -> left)
                queue [rear++] = node -> left;
            if (node -> right)
                queue [rear++] = node -> right;
        }
        if (levelSum > maxSum) {
            maxSum = levelSum;
            maxLevel = level;
        }
        level++;
    }
    free (queue);
    return maxLevel;
}