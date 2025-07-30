class Solution:
    def longestSubarray (self, nums : List [int]) -> int:
        if not nums:
            return 0
        max_val = max (nums)
        max_len = 0
        current_len = 0
        for num in nums:
            if num == max_val:
                current_len += 1
            else:
                max_len = max (max_len, current_len)
                current_len = 0
        return max (max_len, current_len)