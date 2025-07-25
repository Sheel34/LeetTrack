class Solution:
    def maxSum (self, nums : List[int]) -> int:
        freq = [0] * 201
        result = 0; max_num = float ('-inf')
        for i in range (len (nums)):
            freq [nums [i] + 100] += 1
            if nums [i] > max_num: max_num = nums [i]
        for i in range (201):
            num = i - 100
            if freq [i] > 0 and num > 0: result += num
        if result != max_num and result == 0:
            return max_num
        return result
