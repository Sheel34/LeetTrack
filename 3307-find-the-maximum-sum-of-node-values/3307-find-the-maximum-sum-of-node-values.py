class Solution:
    def maximumValueSum(self, nums: List[int], k: int, edges: List[List[int]]) -> int:
        sum = 0
        res = []
        for x in nums:
            sum += x
            y = x ^ k
            res.append(y - x)
        res.sort(reverse=True)
        for i in range(0, len(res) - 1, 2):
            if res[i] + res[i + 1] <= 0:
                break
            sum += res[i] + res[i + 1]
        return sum