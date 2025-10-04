class Solution:
    def maxArea (self, height : List [int]) -> int:
        n = len (height)
        A, l, r = 0, 0, n - 1
        while l < r:
            A = max (A, min (height [l], height [r]) * (r - l))
            if height [r] < height [l]: r -= 1
            else: l += 1
        return A