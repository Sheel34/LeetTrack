int cmp (const void* a, const void* b) {
    int* pa = *(int**) a;
    int* pb = *(int**) b;
    if (pa [0] == pb [0]) return pb [1] - pa [1];
    return pa [0] - pb [0];
}


int numberOfPairs (int** points, int pointsSize, int* pointsColSize) {
    qsort (points, pointsSize, sizeof (int*), cmp);
    int result = 0;
    for (int i = 0; i < pointsSize; i++) {
        int top = points [i] [1];
        int bot = INT_MIN;
        for (int j = i + 1; j < pointsSize; j++) {
            int y = points [j] [1];
            if (bot < y && y <= top) {
                result++;
                bot = y;
                if (bot == top) break;
            }
        }
    }
    return result;
}