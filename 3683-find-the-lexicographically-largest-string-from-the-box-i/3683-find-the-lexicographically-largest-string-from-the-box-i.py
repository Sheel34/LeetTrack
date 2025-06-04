class Solution:
    def answerString(self, word: str, numFriends: int) -> str:
        if numFriends == 1:
            return word
        res = ""
        length = len(word) - numFriends + 1
        for i in range(0, len(word)):
            temp = word[i : i + length]
            if temp > res:
                res = temp
        return res