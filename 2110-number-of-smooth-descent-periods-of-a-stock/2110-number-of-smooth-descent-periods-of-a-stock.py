class Solution:
    def getDescentPeriods (self, prices : List [int]) -> int:
        summ, des, prev = 0, 0, -1
        for x in prices:
            des = (-((x + 1) == prev) & des) + 1
            summ += des
            prev = x
        return summ