from typing import List

class Solution:
    def is_vowel (self, c: str) -> bool:
        return c in "aeiou"

    def mask_vowels (self, s: str) -> str:
        return ''.join ('a' if ch in "aeiou" else ch for ch in s)

    def spellchecker (self, wordlist : List [str], queries : List [str]) -> List [str]:
        exact = set (wordlist)
        lower_map = {}
        vowel_map = {}
        for w in wordlist:
            wl = w.lower ()
            lower_map.setdefault (wl, w)
            masked = self.mask_vowels (wl)
            vowel_map.setdefault (masked, w)
        ans = []
        for q in queries:
            if q in exact:
                ans.append (q)
                continue
            ql = q.lower ()
            if ql in lower_map:
                ans.append (lower_map [ql])
                continue
            qmask = self.mask_vowels (ql)
            ans.append (vowel_map.get (qmask, ""))
        return ans
        