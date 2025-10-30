class Solution:
    def minNumberOperations (self, target : List [int]) -> int:
        return target [0] + sum (max (x - y, 0) for x, y in zip (target [1:], target))