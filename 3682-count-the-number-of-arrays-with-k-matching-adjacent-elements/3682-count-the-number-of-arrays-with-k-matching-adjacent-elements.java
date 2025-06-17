class Solution {
    private static final int MOD = 1_000_000_007;
    private long modpow(long base, int exp) {
        long res = 1;
        while (exp > 0) {
            if ((exp & 1) == 1) res = (res * base) % MOD;
            base = (base * base) % MOD;
            exp >>= 1;
        }
        return res;
    }
    public int countGoodArrays(int n, int m, int k) {
        int d = n - 1;
        if (k > d) return 0;
        int r = k;
        if (r > d - r) r = d - r;
        long C = 1;
        if (r > 0) {
            int[] inv = new int[r + 1];
            inv[1] = 1;
            for (int i = 2; i <= r; ++i) {
                inv[i] = (int)((MOD - (long)(MOD / i) * inv[MOD % i] % MOD) % MOD);
            }
            for (int i = 1; i <= r; ++i) {
                C = C * (d - r + i) % MOD;
                C = C * inv[i] % MOD;
            }
        }
        return (int)((long)m * C % MOD * modpow(m - 1, d - k) % MOD);
    }
}