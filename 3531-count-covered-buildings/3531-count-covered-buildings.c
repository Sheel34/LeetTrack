#pragma GCC optimize ("O3, unroll-loops")

#define SZ 100001

int xMin [SZ], xMax [SZ], yMin [SZ], yMax [SZ];

int countCoveredBuildings (int n, int** buildings, int bz, int* buildingsColSize) {
    int M = 0, N = 0;
    for (int i = 0; i < bz; i++) {
        const int* B = buildings [i];
        const int x = B [0], y = B [1];
        M = fmax (x, M);
        N = fmax (y, N);
    }
    memset (xMax, 0, sizeof (int) * (N + 1));
    memset (yMax, 0, sizeof (int) * (M + 1));
    for (int i = 0; i <= N; i++) xMin [i] = INT_MAX;
    for (int i = 0; i <= M; i++) yMin [i] = INT_MAX;
    for (int i = 0; i < bz; i++) {
        const int* B = buildings [i];
        const int x = B [0], y = B [1];
        xMin [y] = fmin (xMin [y], x);
        xMax [y] = fmax (xMax [y], x);
        yMin [x] = fmin (yMin [x], y);
        yMax [x] = fmax (yMax [x], y);
    }
    int cnt = 0;
    for (int i = 0; i < bz; i++) {
        const int* B = buildings [i];
        const int x = B [0], y = B [1];
        const bool coverX = (xMin [y] < x & x < xMax [y]);
        const bool coverY = (yMin [x] < y & y < yMax [x]);
        cnt += (coverX & coverY);
    }
    return cnt;
}