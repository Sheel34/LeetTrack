int max (int a, int b) { return a > b ? a : b; }

int m, n, dir [] = {-1, 0, 1, 0, -1};

int dfs (int** grid, int i, int j) {
    if (i < 0 || i >= m || j < 0 || j >= n || grid [i] [j] == 0) return 0;
        int sum = grid [i] [j];
        grid [i] [j] = 0;
        for (int k = 0; k < 4; k++)
            sum += dfs (grid, i + dir [k], j + dir [k + 1]);
        return sum;
}

int findMaxFish (int** grid, int gridSize, int* gridColSize) {
    m = gridSize; n = *gridColSize;
    int maxFish = 0;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (grid [i] [j] > 0)
                maxFish = max (maxFish, dfs (grid, i, j));
    return maxFish;
}