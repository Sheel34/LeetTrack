class Solution:
    def minSubarray (self, nums : List [int], p : int) -> int:
        summ = sum (nums)
        target = summ % p
        if target == 0: return 0
        mapp = {0 : -1}
        prefix = 0
        res = len (nums)
        for i, x in enumerate (nums):
            prefix = (prefix + x) % p
            val = (prefix - target + p) % p
            if val in mapp: res = min (res, i - mapp [val])
            mapp [prefix] = i
        return -1 if res == len (nums) else res 