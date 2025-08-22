int minimumArea (int** grid, int gridSize, int* gridColSize) {
    int m = gridSize, n = gridColSize [0];
    int minRow = m, maxRow = -1;
    int minCol = n, maxCol = -1;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) {
                if (i < minRow) minRow = i;
                if (i > maxRow) maxRow = i;
                if (j < minCol) minCol = j;
                if (j > maxCol) maxCol = j;
            }
        }
    }
    return (maxRow - minRow + 1) * (maxCol - minCol + 1);
}