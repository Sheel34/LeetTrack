static long long comb [81] [81];

int countBalancedPermutations (char* num) {
    int n = strlen (num), count [10] = {0}, total = 0;
    for (int i = 0; i < n; i++) {
        int d = num [i] - '0';
        count [d]++;
        total += d;
    }
    if (total & 1) return 0;
    int target = total / 2;
    int oddCount = (n + 1) / 2;
    for (int i = 0; i <= n; i++) {
        comb [i] [0] = 1;
        for (int j = 1; j <= i; j++)
            comb [i] [j] = (comb [i - 1] [j - 1] + comb [i - 1] [j]) % 1000000007;
    }
    int remCount [11];
    remCount [10] = 0;
    for (int d = 9; d >= 0; d--)
        remCount [d] = remCount [d + 1] + count [d];
    static long long dp [362] [82], newdp [362] [82];
    memset (dp, 0, sizeof (dp));
    dp [0] [oddCount] = 1;
    for (int d = 0; d < 10; d++) {
        for (int s = 0; s <= target; s++)
            for (int o = 0; o <= oddCount; o++)
                newdp [s] [o] = 0;
        for (int s = 0; s <= target; s++) {
            for (int o = 0; o <= oddCount; o++) {
                long long waysSoFar = dp [s] [o];
                if (!waysSoFar) continue;
                int maxOdd = count [d] < o ? count [d] : o;
                int evenAvail = remCount [d] - o;
                for (int k = 0; k <= maxOdd; k++) {
                    int e = count [d] - k;
                    if (e > evenAvail) continue;
                    int s2 = s + k * d;
                    if (s2 > target) break;
                    int o2 = o - k;
                    long long chooseOdd = comb [o] [k];
                    long long chooseEven = comb [evenAvail] [e];
                    long long totalWays = (chooseOdd * chooseEven) % 1000000007;
                    newdp [s2] [o2] = (newdp [s2] [o2] + waysSoFar * totalWays) % 1000000007;
                }
            }
        }
        for (int s = 0; s <= target; s++)
            for (int o = 0; o <= oddCount; o++)
                dp [s] [o] = newdp [s] [o];
    }
    return dp [target] [0];
}