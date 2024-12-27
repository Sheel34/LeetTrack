class Solution:
    def maxScoreSightseeingPair(self, values: List[int]) -> int:
        ans = 0
        prev = values [0]

        for i in range (1, len (values)):
            ans = max (ans, prev + values [i] - i)
            prev = max (prev, values [i] + i)
        
        return ans