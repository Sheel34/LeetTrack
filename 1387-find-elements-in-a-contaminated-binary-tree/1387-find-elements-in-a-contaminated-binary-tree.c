/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */



typedef struct {
    struct TreeNode* root;
} FindElements;

struct TreeNode *recover (struct TreeNode *node, int value) {
    if (!node)
        return NULL;
    struct TreeNode *ret = (struct TreeNode*) calloc (1, sizeof (struct TreeNode));
    ret -> val = value;
    ret -> left = recover (node -> left, value * 2 + 1);
    ret -> right = recover (node -> right, value * 2 + 2);
    return ret;
}

FindElements* findElementsCreate (struct TreeNode* root) {
    FindElements *obj = (FindElements*) calloc (1, sizeof (FindElements));
    obj -> root = recover (root, 0);
    return obj;
}

bool traverse (struct TreeNode **node, int target) {
    if (target == 0)
        return true;
    struct TreeNode *next = (*node);
    if (next -> val * 2 + 1 != target && next->val * 2 + 2 != target)
        if (traverse (node, (target - 1) / 2)) {
            next = (*node);
            if (next -> val * 2 + 1 == target && !next -> left)
                return false;
            else if (next -> val * 2 + 2 == target && !next -> right)
                return false;
            else {
                (*node) = (next -> val * 2 + 1 == target) ? next -> left : next -> right;
                return true;
            }
        }
        else
            return false;
    else
        if (next -> val * 2 + 1 == target && !next -> left)
            return false;
        else if (next -> val * 2 + 2 == target && !next -> right)
            return false;
        else {
            (*node) = (next -> val * 2 + 1 == target) ? next -> left : next -> right;
            return true;
        }
}

bool findElementsFind (FindElements* obj, int target) {
    bool ans = false;
    struct TreeNode *node = obj -> root;
    return traverse (&node, target);
}

void freeNode(struct TreeNode *node) {
    if (!node)
        return;
    freeNode (node -> left);
    freeNode (node -> right);
    free (node);
}

void findElementsFree (FindElements* obj) {
    freeNode (obj -> root);
    free (obj);
    return;
}

/**
 * Your FindElements struct will be instantiated and called as such:
 * FindElements* obj = findElementsCreate(root);
 * bool param_1 = findElementsFind(obj, target);
 
 * findElementsFree(obj);
*/