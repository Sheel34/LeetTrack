int numberOfPaths (int** grid, int gridSize, int* gridColSize, int k) {
    const int MOD = 1000000007;
    int m = gridSize, n = gridColSize [0];
    int** prev = malloc (n * sizeof (int*));
    int** curr = malloc (n * sizeof (int*));
    for (int i = 0; i < n; i++) {
        prev[i] = calloc (k, sizeof (int));
        curr [i] = calloc (k, sizeof (int));
    }
    int sum = 0;
    for (int j = 0; j < n; j++) {
        sum = (sum + grid [0] [j]) % k;
        prev [j] [sum] = 1;
    }
    sum = grid [0] [0] % k;
    for (int i = 1; i < m; i++) {
        sum = (sum + grid [i] [0]) % k;
        memset (curr [0], 0, k * sizeof (int));
        curr [0] [sum] = 1;
        for (int j = 1; j < n; j++) {
            memset (curr [j], 0, k * sizeof (int));
            int val = grid [i] [j];
            for (int r = 0; r < k; r++) {
                int nr = (r + val) % k;
                curr [j] [nr] = (prev [j] [r] + curr [j - 1] [r]) % MOD;
            }
        }
        int** tmp = prev;
        prev = curr;
        curr = tmp;
    }
    int ans = prev [n - 1] [0];
    for (int i = 0; i < n; i++) {
        free (prev [i]);
        free (curr [i]);
    }
    free (prev);
    free (curr);
    return ans;
}