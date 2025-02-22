/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
 int dNodes [1001] [2];

struct TreeNode* constructTree (const int * n, int * index, int depth) {
    if ((*index) >= (*n) || dNodes [(*index)] [0] < depth) return NULL;
    struct TreeNode * node = (struct TreeNode *) malloc (sizeof (struct TreeNode));
    node -> val = dNodes [(*index)++] [1];
    node -> left = constructTree (n, index, depth + 1);
    node -> right = constructTree (n, index, depth + 1);
    return node;
}
struct TreeNode* recoverFromPreorder (char* traversal) {
    const int n = strlen (traversal);
    int index = 0;
    for (int i = 0; i < n;) {
        int hCount = 0;
        while (i < n && traversal [i] == '-') {
            i++;
            hCount++;
        }
        int num = 0;
        while (i < n && isdigit (traversal [i])) {
            num = (num * 10) + (traversal [i] - '0');
            i++;
        }
        dNodes [index] [0] = hCount;
        dNodes [index++] [1] = num;
    }
    const int nodes = index;
    index = 0;
    return constructTree (&nodes, &index, 0);
}