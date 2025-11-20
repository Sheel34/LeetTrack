class Solution:
    def countOrders (self, n : int) -> int:
        mod = 10 ** 9 + 7
        count = 1 
        for i in range (2, n + 1):
            count = (count * (2 * i - 1) * i) % mod
        return count % mod