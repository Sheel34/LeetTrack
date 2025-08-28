/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

int cmpAsc (const void* a, const void* b) { 
    return (*(int*) a - *(int*) b); 
}
int cmpDesc (const void* a, const void* b) { 
    return (*(int*) b - *(int*) a); 
}

int** sortMatrix (int** grid, int gridSize, int* gridColSize, int* returnSize, int** returnColumnSizes) {
    *returnSize = gridSize;
    *returnColumnSizes = gridColSize;
    int n = gridSize, m = gridColSize [0];
    int diagCount = n + m - 1;
    int* sizes = (int*) calloc (diagCount, sizeof (int));
    int** diags = (int**) malloc (diagCount * sizeof (int*));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            sizes [i - j + m - 1]++;
    for (int k = 0; k < diagCount; k++) {
        diags [k] = (int*) malloc (sizes [k] * sizeof (int));
        sizes [k] = 0;
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            diags [i - j + m - 1] [sizes [i - j + m - 1]++] = grid [i] [j];
    for (int k = 0; k < diagCount; k++) {
        if (k < m - 1) qsort (diags [k], sizes [k], sizeof (int), cmpAsc);
        else qsort (diags [k], sizes [k], sizeof (int), cmpDesc);
        sizes [k] = 0;
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            grid [i] [j] = diags [i - j + m - 1] [sizes [i - j + m - 1]++];
    return grid;
}