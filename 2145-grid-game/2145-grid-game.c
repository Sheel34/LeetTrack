inline long long max (long long a, long long b) { return (a > b) ? a : b; }
inline long long min (long long a, long long b) { return (a < b) ? a : b; }
inline long long add_operation (long long a, long long b) { return a + b; }

long long accumulate (const int* const arr, int arrSize, long long (*operation) (long long, long long)) {
    long long result = 0LL;
    for (int i = 0; i < arrSize; i++) {
        result = operation (result, (long long) arr [i]);
    }
    return result;
}

long long gridGame (int** grid, int gridSize, int* gridColSize) {
    const int n = gridColSize [0];
    long long result = LLONG_MAX;
    long long sumRow0 = accumulate (grid [0], n, add_operation);
    long long sumRow1 = 0LL;

    for (int i = 0; i < n; i++) {
        sumRow0 -= grid [0] [i];
        result = min (result, max (sumRow0, sumRow1));
        sumRow1 += grid [1] [i];
    }
    return result;
}