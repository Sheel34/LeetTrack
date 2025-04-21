class Solution:
    def numberOfArrays (self, differences : List [int], lower : int, upper : int) -> int:
        a = maxx = minn = 0
        for i in differences:
            a += i
            maxx = max (maxx, a)
            minn = min (minn, a)
        return max (0, (upper - lower) - (maxx - minn) + 1)