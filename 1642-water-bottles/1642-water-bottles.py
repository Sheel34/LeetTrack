class Solution:
    def numWaterBottles (self, b : int, n : int) -> int:
        return int (b + (b - 1) / (n - 1))