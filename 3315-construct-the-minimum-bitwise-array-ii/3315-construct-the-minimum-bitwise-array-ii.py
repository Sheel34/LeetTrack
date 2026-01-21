class Solution:
    def minBitwiseArray (self, nums : List [int]) -> List[int]:
        answer = [0] * len (nums)
        for i in range (len (nums)):
            k, n, ans = nums [i], 1, -1 
            while (k & n) != 0:
                ans = k - n
                n <<= 1
            answer [i] = ans
        return answer