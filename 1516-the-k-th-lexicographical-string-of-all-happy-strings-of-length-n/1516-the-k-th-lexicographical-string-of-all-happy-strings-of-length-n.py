class Solution:
    def getHappyString (self, n : int, k : int) -> str:
        def dfs (prefix, n, k):
            if n == 0:
                return prefix
            for c in 'abc':
                if prefix and c == prefix [-1]:
                    continue
                count = 2 ** (n2 - len (prefix) - 1)
                if count >= k:
                    return dfs (prefix + c, n - 1, k)
                else:
                    k -= count
            return ""
        
        n2 = n
        return dfs ("", n, k)