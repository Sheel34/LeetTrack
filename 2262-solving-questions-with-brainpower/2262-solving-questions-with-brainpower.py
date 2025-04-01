class Solution:
    def mostPoints (self, questions : List [List [int]]) -> int:
        n = len (questions)
        @cache
        def dfs (i):
            if i >= n: return 0
            pt, skip = questions [i]
            return max (pt + dfs (i + skip + 1), dfs (i + 1))
        return dfs (0)