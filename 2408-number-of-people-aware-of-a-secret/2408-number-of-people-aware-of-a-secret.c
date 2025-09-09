int peopleAwareOfSecret (int n, int delay, int forget) {
    const long long MOD = 1000000007LL;
    if (n == 1) return 1;
    long long *dp = (long long*) calloc (n + 1, sizeof (long long));
    dp [1] = 1;
    long long window = 0;
    for (int i = 2; i <= n; ++i) {
        int enter = i - delay;
        int exit = i - forget;
        if (enter >= 1) window = (window + dp [enter]) % MOD;
        if (exit >= 1) window = (window - dp [exit] + MOD) % MOD;
        dp [i] = window;
    }
    long long ans = 0;
    int start = n - forget + 1;
    if (start < 1) start = 1;
    for (int i = start; i <= n; ++i) ans = (ans + dp [i]) % MOD;
    int res = (int) ans;
    free (dp);
    return res;
}