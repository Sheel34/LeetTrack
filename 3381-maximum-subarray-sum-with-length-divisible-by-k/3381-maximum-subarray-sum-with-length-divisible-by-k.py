class Solution:
    def maxSubarraySum (self, nums : List [int], k : int) -> int:
        minn = [inf] * (k - 1) + [0]
        prefix, res = 0, -inf
        for i, x in enumerate (nums):
            prefix += x
            d = i % k
            res = max (res, prefix - minn [d])
            minn [d] = min (minn [d], prefix)
        return res