int compare (const void* a, const void* b) {
    return *(int*) a - *(int*) b;
}

int minOperations (int** grid, int gridSize, int* gridColSize, int x) {
    int result = 0, i, j, m, arr [gridSize * gridColSize [0]], arrSize = 0;
    for (i = 0, m = grid [0] [0] % x; i < gridSize; i++) {
        for (j = 0; j < gridColSize [i]; j++) {
            if (grid [i] [j] % x != m) { return -1; }
            arr [arrSize++] = grid [i] [j];
        }
    }
    qsort (arr, arrSize, sizeof (int), compare);
    for (i = 0, m = arr [arrSize / 2]; i < arrSize; i++)
    { result += abs (m - arr [i]) / x; }
    return result;
}