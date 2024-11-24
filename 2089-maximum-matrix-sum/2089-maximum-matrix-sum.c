long long maxMatrixSum(int** matrix, int matrixSize, int* matrixColSize) {
    
    long long sum = 0;
    int minVal = INT_MAX, negCount = 0, zeroCount = 0;
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixColSize [i]; j++) {
            int cell = matrix [i] [j];
            if (cell < 0) {
                sum -= cell;
                negCount++;
                if (-cell < minVal) minVal = -cell;
            } else if (cell == 0) {
                zeroCount++;
                if (0 < minVal) minVal = 0;
            } else {
                sum += cell;
                if (cell < minVal) minVal = cell;
            }
        }
    }
    return (zeroCount > 0 || negCount % 2 == 0) ? sum : sum - 2 * minVal;
}