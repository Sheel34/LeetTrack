int minTimeToReach (int** A, int ASize, int* AColSize) {
    int n = ASize;
    if (n == 0) return -1;
    int m = AColSize [0];
    int total = n * m;
    int *dp = malloc (total * sizeof (int));
    for (int i = 0; i < total; i++) dp [i] = INT_MAX;
    dp [0] = 0;
    int *heap = malloc (total * sizeof (int));
    int hsize = 0;
    heap [hsize++] = 0;
    int dirs [4] [2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    while (hsize) {
        int u = heap [0];
        heap [0] = heap [--hsize];
        int i = 0;
        while (1) {
            int l = 2 * i + 1, r = 2 * i + 2, best = i;
            if (l < hsize && dp [heap [l]] < dp [heap [best]]) best = l;
            if (r < hsize && dp [heap [r]] < dp [heap [best]]) best = r;
            if (best == i) break;
            int tmp = heap [i]; heap [i] = heap [best]; heap [best] = tmp;
            i = best;
        }
        if (u == total - 1) break;
        int t = dp [u];
        int x = u / m, y = u % m;
        for (int d = 0; d < 4; d++) {
            int nx = x + dirs [d] [0], ny = y + dirs [d] [1];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            int idx = nx * m + ny;
            int w = (A [nx] [ny] > t ? A [nx] [ny] : t) + 1;
            if (w < dp [idx]) {
                dp [idx] = w;
                int j = hsize;
                heap [hsize++] = idx;
                while (j > 0 && dp [heap [j]] < dp [heap [(j - 1) / 2]]) {
                    int p = (j - 1) / 2;
                    int tmp = heap [j]; heap [j] = heap [p]; heap [p] = tmp;
                    j = p;
                }
            }
        }
    }
    int ans = dp [total - 1];
    free (dp);
    free (heap);
    return ans;
}