void flip(int* row, int size, int* flippedRow) 
{
    for (int i = 0; i < size; ++i) {
        flippedRow[i] = 1 - row[i];
    }
}

bool isEqual(int* row1, int* row2, int size) 
{
    for (int i = 0; i < size; ++i) {
        if (row1[i] != row2[i]) {
            return false;
        }
    }
    return true;
}

int maxEqualRowsAfterFlips(int** matrix, int matrixSize, int* matrixColSize) {
    
    int maxCount = 0;

    for (int i = 0; i < matrixSize; ++i) {
        int count = 1;
        int* flippedRow = (int*)malloc((*matrixColSize) * sizeof(int));
        flip(matrix[i], *matrixColSize, flippedRow);

        for (int j = i + 1; j < matrixSize; ++j) {
            if (isEqual(matrix[i], matrix[j], *matrixColSize) || 
                isEqual(flippedRow, matrix[j], *matrixColSize)) {
                ++count;
            }
        }
        maxCount = maxCount > count ? maxCount : count;
        free(flippedRow);
    }

    return maxCount;
}