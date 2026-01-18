bool isValid (int** grid, int i, int j, int k) {
    int sum = 0;
    for (int x = i; x < i + k; x++) {
        int s = 0;
        for (int y = j; y < j + k; y++) s += grid [x] [y];
        if (x == i) sum = s;
        else if (sum != s) return false;
    }
    for (int y = j; y < j + k; y++) {
        int s = 0;
        for (int x = i; x < i + k; x++) s += grid [x] [y];
        if (sum != s) return false;
    }
    int s = 0;
    for (int d = 0; d < k; d++) s += grid [i + d] [j + d];
    if (sum != s) return false;
    s = 0;
    for (int d = 0; d < k; d++) s += grid [i + d] [j + k - 1 - d];
    if (sum != s) return false;
    return true;
}

int largestMagicSquare (int** grid, int gridSize, int* gridColSize) {
    int m = gridSize, n = gridColSize [0];
    int res = 1;
    for (int k = 2; k <= (m < n ? m : n); k++)
        for (int i = 0; i + k <= m; i++)
            for (int j = 0; j + k <= n; j++)
                if (isValid (grid, i, j, k)) res = k;
    return res;
}