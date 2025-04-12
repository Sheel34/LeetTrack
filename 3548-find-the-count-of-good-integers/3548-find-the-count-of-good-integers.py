class Solution:
    def countGoodIntegers (self, n : int, k : int) -> int:
        base = 10 ** ((n + 1) // 2)
        encoded_freqs = set ()
        for half in range (base // 10, base):
            half_str = str (half)
            full_str = half_str + half_str [:-1] [::-1] if n % 2 else half_str + half_str [::-1]
            num = int (full_str)
            if num % k == 0:
                freq = [0] * 10
                for ch in full_str:
                    freq [int (ch)] += 1
                encoded = 0
                for f in freq:
                    encoded = encoded * 11 + f
                encoded_freqs.add (encoded)
        total = 0
        for code in encoded_freqs:
            freq = [0] * 10
            for i in reversed (range (10)):
                freq [i] = code % 11
                code //= 11
            rem = n
            ways = 1
            for i in range (10):
                if freq [i] > rem:
                    ways = 0
                    break
                if i == 0:
                    ways *= comb (rem - 1, freq [i])
                else:
                    ways *= comb (rem, freq [i])
                rem -= freq [i]
            total += ways
        return total