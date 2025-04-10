static long long dp[35][2];

long long solve(int tight, int idx, const char *t, int len_t, const char *s, int len_s, int limit) {
    if (idx == len_t)
        return 1LL;
    if (dp [idx] [tight] != -1)
        return dp [idx] [tight];
    long long ans = 0;
    int mx = (tight ? (t [idx] - '0') : limit);
    if(mx > limit)
        mx = limit;
    int posSuffix = len_t - len_s;
    for (int d = 0; d <= mx; d++) {
        if (idx >= posSuffix) {
            int suffixIndex = idx - posSuffix;
            if (d != s [suffixIndex] - '0')
                continue;
        }
        int next_tight = (tight && (d == (t [idx] - '0')));
        ans += solve (next_tight, idx + 1, t, len_t, s, len_s, limit);
    }
    dp [idx] [tight] = ans;
    return ans;
}

long long numberOfPowerfulInt (long long start, long long finish, int limit, char* s) {
    char t [35], t1 [35];
    sprintf (t, "%lld", finish);
    long long st = start - 1;
    sprintf (t1, "%lld", st);
    long long countFinish = 0, countStart = 0;
    int len_t = strlen (t);
    int len_s = strlen (s);
    if (len_t < len_s) {
        countFinish = 0;
    } else {
        for (int i = 0; i < len_t; i++) {
            for (int j = 0; j < 2; j++)
                dp [i] [j] = -1;
        }
        countFinish = solve (1, 0, t, len_t, s, len_s, limit);
    }
    int len_t1 = strlen (t1);
    if (len_t1 < len_s)
        countStart = 0;
    else {
        for (int i = 0; i < len_t1; i++) {
            for (int j = 0; j < 2; j++)
                dp [i] [j] = -1;
        }
        countStart = solve (1, 0, t1, len_t1, s, len_s, limit);
    }
    return countFinish - countStart;
}