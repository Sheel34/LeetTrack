class Solution:
    def makeFancyString (self, s : str) -> str:
        d = defaultdict (int)
        k = ''
        a = 0
        l = s [0]
        for i in s:
            if i == l:
                a += 1
                if a < 3:
                    k += i
            elif i != l:
                a = 1
                k += i
                l = i
        return k   