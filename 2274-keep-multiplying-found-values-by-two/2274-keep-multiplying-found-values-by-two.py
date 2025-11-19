class Solution:
    def findFinalValue (self, nums : List [int], original : int) -> int:
        bits = 0
        for num in nums:
            if num % original != 0:
                continue
            n = num // original
            if n & (n - 1) == 0:
                bits |= n
        d = bits + 1
        return original * (d & -d)