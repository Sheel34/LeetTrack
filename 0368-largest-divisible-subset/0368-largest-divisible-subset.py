class Solution:
    def largestDivisibleSubset (self, nums : List [int]) -> List [int]:
        if not nums:
            return []
        nums.sort ()
        result = [[num] for num in nums]
        for i in range (1, len (nums)):
            for j in range (i):
                if (nums [i] % nums [j] == 0 and len (result [i]) < len (result [j]) + 1):
                    result [i] = result [j] + [nums [i]]
        maxSubset = max (result, key = len)
        return maxSubset