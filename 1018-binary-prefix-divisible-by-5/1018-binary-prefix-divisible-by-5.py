class Solution:
    def prefixesDivBy5(self, nums: List[int]) -> List[bool]:
        ans = [0] * len (nums)
        msb = 0
        for i in range (len (nums)):
            msb = (msb << 1) + nums [i]
            msb -= (-(msb >= 5) & 5)
            ans [i] = msb == 0
        return ans