class Solution:
    def shortestCommonSupersequence (self, str1 : str, str2 : str) -> str:
        n, m = len (str1), len (str2)
        dp = [[0] * (m + 1) for _ in range(n + 1)]

        for j in range (m):
            dp [n] [j] = m - j
        
        for i in range (n - 1, -1, -1):
            dp [i] [m] = n - i
            for j in range (m - 1, -1, -1):
                if str1 [i] == str2 [j]:
                    dp [i] [j] = 1 + dp [i + 1] [j + 1]
                else:
                    dp [i] [j] = 1 + min (dp [i + 1] [j], dp [i] [j + 1])
        res = ""
        i = j = 0
        while i < n and j < m:
            if str1 [i] == str2 [j]:
                res += str1 [i]
                i += 1
                j += 1
            elif dp [i + 1] [j] <= dp [i] [j + 1]:
                res += str1 [i]
                i += 1
            else:
                res += str2 [j]
                j += 1
        return res + str1 [i:] + str2 [j:]