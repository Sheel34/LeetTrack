/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int find (int* parent, int x) {
    if (parent [x] != x) {
        parent [x] = find (parent, parent [x]);
    }
    return parent [x];
}

void unionSet (int* parent, int* rank, int x, int y) {
    int rootX = find (parent, x);
    int rootY = find (parent, y);
    if (rootX != rootY) {
        if (rank [rootX] > rank [rootY]) {
            parent [rootY] = rootX;
        } else if (rank [rootX] < rank [rootY]) {
            parent [rootX] = rootY;
        } else {
            parent [rootY] = rootX;
            rank [rootX]++;
        }
    }
}

int* findRedundantConnection (int** edges, int edgesSize, int* edgesColSize, int* returnSize) {
    int* parent = (int*) malloc ((edgesSize + 1) * sizeof (int));
    int* rank = (int*) calloc ((edgesSize + 1), sizeof (int));
    
    for (int i = 1; i <= edgesSize; i++) {
        parent [i] = i;
    }
    
    int* result = (int*) malloc (2 * sizeof (int));
    *returnSize = 2;
    
    for (int i = 0; i < edgesSize; i++) {
        int u = edges [i] [0], v = edges [i] [1];
        if (find (parent, u) == find (parent, v)) {
            result [0] = u;
            result [1] = v;
        } else {
            unionSet (parent, rank, u, v);
        }
    }
    
    free (parent);
    free (rank);
    return result;
}