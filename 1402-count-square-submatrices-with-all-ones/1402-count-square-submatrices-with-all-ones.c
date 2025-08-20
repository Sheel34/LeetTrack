int countSquares (int** matrix, int matrixSize, int* matrixColSize) {
    if (matrixSize == 0 || matrixColSize [0] == 0) return 0;
    int m = matrixSize;
    int n = matrixColSize [0];
    int res = 0;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            if (matrix [i] [j] == 1 && i > 0 && j > 0) {
                int minVal = matrix [i - 1] [j];
                if (matrix [i] [j-1] < minVal) minVal = matrix [i] [j - 1];
                if (matrix [i - 1] [j - 1] < minVal) minVal = matrix [i - 1] [j - 1];
                matrix [i] [j] = minVal + 1;
            }
            res += matrix [i] [j];
        }
    return res;
}