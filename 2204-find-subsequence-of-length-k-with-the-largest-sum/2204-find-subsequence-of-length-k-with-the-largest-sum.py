class Solution:
    def maxSubsequence (self, nums : List [int], k : int) -> List [int]:
        for i in range (len (nums)-k):
            nums.remove (min (nums))
        return nums