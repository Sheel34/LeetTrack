/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* createTreeNode (int val) {
    struct TreeNode* new_tree_node = (struct TreeNode*) malloc (sizeof (struct TreeNode));
    new_tree_node -> val = val;
    new_tree_node -> left = NULL;
    new_tree_node -> right = NULL;
    return new_tree_node;
}

struct StackElement {
    struct TreeNode* node;
    struct StackElement* next;
};

struct Stack {
    struct StackElement* top;
};

struct StackElement* createStackElement (struct TreeNode* node) {
    struct StackElement* new_stack_element = (struct StackElement*) malloc (sizeof (struct StackElement));
    new_stack_element -> node = node;
    new_stack_element -> next = NULL;
    return new_stack_element;
}

struct Stack* createStack () {
    struct Stack* new_stack = (struct Stack*) malloc (sizeof (struct Stack));
    new_stack -> top = NULL;
    return new_stack;
}

void deleteStackElement (struct StackElement* stack_element) {
    free (stack_element);
}

struct TreeNode* peekStack (struct Stack* stack) {
    struct StackElement* top_element = stack -> top;
    if (top_element) return top_element -> node;
    return NULL;
}

void addToStack (struct Stack* stack, struct TreeNode* node) {
    struct StackElement* new_stack_element = createStackElement (node);
    new_stack_element -> next = stack -> top;
    stack -> top = new_stack_element;
}

struct TreeNode* popFromStack (struct Stack* stack) {
    struct StackElement* top_element = stack -> top;
    if (top_element) {
        stack -> top = top_element -> next;
        struct TreeNode* node_to_return = top_element -> node;
        deleteStackElement (top_element);
        return node_to_return;
    }
    return NULL;
}

void deleteStack (struct Stack* stack) {
    while (popFromStack (stack));
    free (stack);
}

struct TreeNode* constructFromPrePost (int* preorder, int preorderSize, int* postorder, int postorderSize) {
    struct Stack* stack = createStack ();
    struct TreeNode* root = NULL;
    int pre_order_pointer = 0; 
    int post_order_pointer = 0;
    while (pre_order_pointer < preorderSize) {
        struct TreeNode* new_node = createTreeNode (preorder [pre_order_pointer]);
        struct TreeNode* parent = peekStack (stack);
        if (!parent) root = new_node;
        else if (parent -> left) parent -> right = new_node;
        else parent -> left = new_node;
        if (preorder [pre_order_pointer] == postorder [post_order_pointer]) {
            post_order_pointer++;
            while (peekStack (stack) && postorder [post_order_pointer] == peekStack (stack) -> val) {
                popFromStack (stack);
                post_order_pointer++;
            }
        }
        else addToStack (stack, new_node);
        pre_order_pointer++;
    }
    deleteStack (stack);
    return root;
}