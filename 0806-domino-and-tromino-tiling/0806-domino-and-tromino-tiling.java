class Solution {
    ArrayList <Integer> dp = new ArrayList <> (Collections.nCopies (1001, -1)); 
    final int MOD = 1_000_000_007;
    public int solve (int n) {
        if (n == 0) return 0;
        if (n == 1) return 1;
        if (n == 2) return 2;
        if (n == 3) return 5;
        if (dp.get (n) != -1) return dp.get (n);
        long part1 = (2L * solve (n - 1)) % MOD;
        long part2 = solve (n - 3) % MOD;
        int result = (int) ((part1 + part2) % MOD);
        dp.set (n, result);
        return result;
    }
    public int numTilings (int n) {
        return solve (n);
    }
}