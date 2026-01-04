class Solution {
    public int sumFourDivisors (int [] nums) {
        int maxNum = 0;
        for (int x : nums) if (x > maxNum) maxNum = x;
        if (maxNum < 2) return 0;
        buildSieve (maxNum);
        int total = 0;
        for (int x : nums) {
            int p = (int) Math.round (Math.cbrt (x));
            if ((long) p * p * p == x && p >= 0 && p < sieve.length && sieve[p]) {
                total += 1 + p + p*p + x;
                continue;
            }
            for (int i = 2; i * i <= x; i++) {
                if (x % i == 0) {
                    int j = x / i;
                    if (i != j && i < sieve.length && j < sieve.length && sieve [i] && sieve[j]) {
                        total += 1 + i + j + x;
                    }
                    break;
                }
            }
        }
        return total;
    }
    private boolean [] sieve;

    private void buildSieve (int n) {
        sieve = new boolean [n + 1];
        Arrays.fill (sieve, true);
        if (n >= 0) sieve [0] = false;
        if (n >= 1) sieve [1] = false;
        for (int i = 2; i * i <= n; i++) {
            if (sieve[i]) {
                for (int j = i * i; j <= n; j += i) sieve [j] = false;
            }
        }
    }
}