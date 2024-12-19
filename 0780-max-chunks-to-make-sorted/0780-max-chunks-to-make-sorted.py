class Solution:
    def maxChunksToSorted (self, arr : List [int]) -> int:
        return list (accumulate (x - i for i, x in enumerate (arr))).count (0)