class Solution:
    def lengthAfterTransformations (self, s : str, t : int) -> int:
        MOD = 1000000007
        freq = [0] * 26
        for c in s:
            freq [ord (c) - ord ('a')] += 1
        while t >= 26:
            z = freq [25]
            for i in range (24, -1, -1):
                freq [i + 1] = (freq [i + 1] + freq [i]) % MOD
            freq [0] = (freq [0] + z) % MOD
            freq [1] = (freq [1] + z) % MOD
            t -= 26
        res = 0
        for i in range (25, -1, -1):
            if i + t > 25:
                res = (res + freq [i]) % MOD
            res = (res + freq [i]) % MOD
        return res