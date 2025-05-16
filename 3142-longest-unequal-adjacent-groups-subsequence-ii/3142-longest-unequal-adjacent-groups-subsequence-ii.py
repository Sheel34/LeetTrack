class Solution:
    def getWordsInLongestSubsequence(self, words: List[str], groups: List[int]) -> List[str]:
        def pack(w: str) -> int:
            code = 0
            for i, ch in enumerate(w):
                code |= (ord(ch) - 97) << (5 * i)
            return code

        n = len(words)
        dp = [1] * n
        prev = [-1] * n
        max_len = 1
        max_idx = 0
        patterns_by_len = {}
        codes = [pack(w) for w in words]
        for i, w in enumerate(words):
            L = len(w)
            g_i = groups[i]
            code_i = codes[i]
            buckets = patterns_by_len.setdefault(L,
                      [defaultdict(list) for _ in range(L)])
            best_len = 1
            best_prev = -1
            for j in range(L):
                mask = ~(31 << (5 * j))
                pat = code_i & mask
                for k in buckets[j].get(pat, ()):
                    if groups[k] != g_i and dp[k] + 1 > best_len:
                        best_len = dp[k] + 1
                        best_prev = k
            dp[i] = best_len
            prev[i] = best_prev
            for j in range(L):
                mask = ~(31 << (5 * j))
                pat = code_i & mask
                buckets[j].setdefault(pat, []).append(i)
            if best_len > max_len:
                max_len = best_len
                max_idx = i

        res = []
        cur = max_idx
        while cur != -1:
            res.append(words[cur])
            cur = prev[cur]
        return res[::-1]