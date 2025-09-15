class Solution:
    def canBeTypedWords (self, text : str, brokenLetters : str) -> int:
        broken = set (brokenLetters)
        count = 0
        for w in text.split ():
            if not any (ch in broken for ch in w):
                count += 1
        return count