class Solution {
    public int lengthAfterTransformations (String s, int t) {
        int MOD = 1000000007;
        long [] freq = new long [26];
        for (int i = 0; i < s.length (); i++)
            freq [s.charAt (i) - 'a']++;
        while (t >= 26) {
            long z = freq [25];
            for (int i = 24; i >= 0; i--)
                freq [i + 1] = (freq [i + 1] + freq [i]) % MOD;
            freq [0] = (freq [0] + z) % MOD;
            freq [1] = (freq [1] + z) % MOD;
            t -= 26;
        }
        long res = 0;
        for (int i = 25; i >= 0; i--) {
            if (i + t > 25)
                res = (res + freq [i]) % MOD;
            res = (res + freq [i]) % MOD;
        }
        return (int) res;
    }
}