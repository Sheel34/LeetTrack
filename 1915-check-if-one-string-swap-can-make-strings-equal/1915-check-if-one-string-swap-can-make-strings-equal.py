class Solution:
    def areAlmostEqual (self, s1 : str, s2 : str) -> bool:
        i =- 1
        j =- 1
        count = 0
        for k in range (0, len (s1)):
            if s1 [k] != s2 [k]:
                count += 1
                if i == -1: i = k
                elif j == -1: j = k
        
        if count == 0: return True
        elif count == 2 and s1 [i] == s2 [j] and s1 [j] == s2 [i]: return True

        return False