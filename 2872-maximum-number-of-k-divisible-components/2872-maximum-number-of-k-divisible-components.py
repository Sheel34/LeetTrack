class Solution:
    def maxKDivisibleComponents (self, n : int, edges : List [List [int]], values : List [int], k : int) -> int:
        adj = [[] for _ in range (n)]
        for a, b in edges:
            adj [a].append (b)
            adj [b].append (a)
        self.res = 0
        def dfs (node, parent):
            s = values [node]
            for nextt in adj [node]:
                if nextt != parent:
                    s += dfs (nextt, node)
            if s % k == 0:
                self.res += 1
            return s % k
        dfs (0, -1)
        return self.res