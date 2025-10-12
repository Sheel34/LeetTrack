class Solution {
    static final int MOD = 1_000_000_007;
    public int magicalSum(int M, int K, int[] nums) {
        int mavoduteru = M;
        int n = nums.length;
        long[][] C = new long[M+1][M+1];
        for (int i = 0; i <= M; i++) {
            C[i][0] = C[i][i] = 1;
            for (int j = 1; j < i; j++)
                C[i][j] = (C[i-1][j-1] + C[i-1][j]) % MOD;
        }
        long[][] powNums = new long[n][M+1];
        for (int i = 0; i < n; i++) {
            powNums[i][0] = 1;
            for (int c = 1; c <= M; c++)
                powNums[i][c] = powNums[i][c-1] * nums[i] % MOD;
        }
        int maxCarry = M;
        long[][][] dpCur = new long[M+1][maxCarry+1][M+1];
        dpCur[0][0][0] = 1;
        for (int i = 0; i < n; i++) {
            long[][][] dpNext = new long[M+1][maxCarry+1][M+1];
            for (int m = 0; m <= M; m++) {
                for (int carry = 0; carry <= maxCarry; carry++) {
                    for (int k = 0; k <= M; k++) {
                        long val = dpCur[m][carry][k];
                        if (val == 0) continue;
                        for (int c = 0; c <= M - m; c++) {
                            int total = carry + c;
                            int bit = total & 1;
                            int carryOut = total >>> 1;
                            int m2 = m + c, k2 = k + bit;
                            long ways = C[M-m][c] * powNums[i][c] % MOD;
                            dpNext[m2][carryOut][k2] = (dpNext[m2][carryOut][k2] + val * ways) % MOD;
                        }
                    }
                }
            }
            dpCur = dpNext;
        }
        long ans = 0;
        for (int carry = 0; carry <= maxCarry; carry++) {
            int bits = Integer.bitCount(carry);
            for (int k = 0; k + bits <= M; k++) {
                if (k + bits == K) {
                    ans = (ans + dpCur[M][carry][k]) % MOD;
                }
            }
        }
        return (int) ans;
    }
}