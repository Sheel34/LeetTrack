class Solution:
    def closestPrimes (self, left : int, right : int) -> List [int]:
        def is_prime (n):
            if n <= 1:
                return False
            if n <= 3:
                return True
            if n % 2 == 0 or n % 3 == 0:
                return False
            i = 5
            while i * i <= n:
                if n % i == 0 or n % (i + 2) == 0:
                    return False
                i += 6
            return True
        primes = []
        for num in range (max (2, left), right + 1):
            if is_prime (num):
                primes.append (num)
        if len (primes) < 2:
            return [-1, -1]
        min_gap = float ('inf')
        result = [-1, -1]
        for i in range (1, len (primes)):
            gap = primes [i] - primes [i - 1]
            if gap < min_gap:
                min_gap = gap
                result = [primes [i - 1], primes [i]]
        return result