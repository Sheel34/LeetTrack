/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

struct disjointSetContainer{
    int* parent;
    int* cost;
};

int get_root (struct disjointSetContainer* set, int node) {
    if (set -> parent [node] == node)
        return node; 
    return set -> parent [node] = get_root (set, set -> parent [node]);
}

int* minimumCost (int n, int** edges, int edgesSize, int* edgesColSize, int** query, int querySize, int* queryColSize, int* returnSize) {
    struct disjointSetContainer set = {
        .parent = malloc (n * sizeof(int)),
        .cost = malloc (n * sizeof(int))
    };
    for (int i = 0; i < n; i++) {
        set.parent [i] = i;
        set.cost [i] = INT_MAX;
    }
    for (int i = 0; i < edgesSize; i++) {
        int u_root = get_root (&set, edges [i] [0]);
        int v_root = get_root (&set, edges [i] [1]);
        set.cost[u_root] &= edges [i] [2];
        if (v_root != u_root) {
            set.parent [v_root] = u_root;
            set.cost [u_root] &= set.cost [v_root];
        }
    }
    int* ans = malloc (querySize * sizeof (int));
    *returnSize = querySize;
    for (int i = 0; i < querySize; i++) {
        if (query [i] [0] == query [i] [1]) {
            ans [i] == 0;
            continue;
        }
        int s_root = get_root (&set, query [i] [0]);
        if (s_root == get_root (&set, query [i] [1]))
            ans [i] = set.cost [s_root];
        else
            ans [i] = -1;
    }
    free (set.parent);
    free (set.cost);
    return ans;
}