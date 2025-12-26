class Solution:
    def bestClosingTime (self, customers : str) -> int:
        bestTime = 0; mmin = 0; pre = 0
        for i in range (len (customers)):
            pre += -1 if customers [i] == 'Y' else 1
            if pre < mmin:
                bestTime = i + 1
                mmin = pre
        return bestTime