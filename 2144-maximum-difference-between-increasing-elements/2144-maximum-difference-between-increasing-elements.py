class Solution:
    def maximumDifference(self, nums: List[int]) -> int:
        diff = -1
        mn = nums[0]
        
        for i in range(1, len(nums)):
            if nums[i] > mn:
                diff = max(diff, nums[i] - mn)
            if nums[i] < mn:
                mn = nums[i]
        
        return diff