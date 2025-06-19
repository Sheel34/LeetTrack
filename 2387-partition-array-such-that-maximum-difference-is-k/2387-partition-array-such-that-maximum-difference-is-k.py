class Solution:
    def partitionArray (self, nums: List[int], k: int) -> int:
        return len ({*accumulate (sorted (nums), lambda q, v : (q, v) [v - q > k])})