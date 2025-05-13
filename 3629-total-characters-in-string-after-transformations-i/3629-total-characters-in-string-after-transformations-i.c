int lengthAfterTransformations (char* s, int t) {
    int MOD = 1000000007;
        long long freq [26] = {};
        for (int i = 0; i < strlen (s); i++)
            freq [s [i] - 'a']++;
        while (t >= 26) {
            long long z = freq [25];
            for (int i = 24; i >= 0; i--)
                freq [i + 1] = (freq [i + 1] + freq [i]) % MOD;
            freq [0] += z;
            freq [1] += z;
            t -= 26;
        }
        int res = 0;
        for (int i = 25; i >= 0; i--){
            if (i + t > 25)
                res = (res + freq [i]) % MOD;
            res = (res + freq [i]) % MOD;
        }
        return res;
}