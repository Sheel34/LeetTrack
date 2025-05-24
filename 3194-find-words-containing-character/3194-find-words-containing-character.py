class Solution:
    def findWordsContaining(self, words: List[str], x: str) -> List[int]:
        res = []
        for i, w in enumerate(words):
            if w.find(x) != -1:
                res.append(i)
        return res