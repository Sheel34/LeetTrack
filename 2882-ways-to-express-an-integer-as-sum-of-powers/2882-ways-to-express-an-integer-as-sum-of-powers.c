#define MOD 1000000007

int numberOfWays (int n, int x) {
    int capacity = 16;
    int *powers = (int*) malloc (sizeof (int) * capacity);
    int pc = 0;
    for (int i = 1; ; ++i) {
        long long p = 1;
        for (int k = 0; k < x; ++k) p *= i;
        if (p > n) break;
        if (pc >= capacity) {
            capacity *= 2;
            powers = (int*) realloc (powers, sizeof (int) * capacity);
        }
        powers [pc++] = (int) p;
    }
    long long *dp = (long long*) calloc (n + 1, sizeof (long long));
    dp [0] = 1;
    for (int i = 0; i < pc; ++i) {
        int p = powers [i];
        for (int s = n; s >= p; --s)
            dp [s] = (dp [s] + dp [s - p]) % MOD;
    }
    int ans = (int) (dp [n] % MOD);
    free (powers);
    free (dp);
    return ans;
}