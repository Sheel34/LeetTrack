class Solution:
    def minimumOperations (self, nums: List [int]) -> int:
        ans = 0
        while True:
            count = defaultdict (int)
            isDistinct = True
            for n in nums [ans * 3 :]:
                count [n] += 1
                if count [n] > 1:
                    isDistinct = False
                    break
            if isDistinct:
                return ans
            ans += 1