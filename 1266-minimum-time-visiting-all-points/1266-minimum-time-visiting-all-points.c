int minTimeToVisitAllPoints (int** p, int pointsSize, int* pointsColSize) {
    int ans = 0;
    for (int i = 1; i < pointsSize; i++)
        ans += fmax ( abs (p [i] [0] - p [i - 1] [0]), abs (p [i] [1] - p [i - 1] [1])
        );
    return ans;
}