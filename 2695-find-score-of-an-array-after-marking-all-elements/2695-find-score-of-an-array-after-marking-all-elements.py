class Solution:
    def findScore (self, nums : List [int]) -> int:
        score = 0
        n = len (nums)
        q = deque ()

        for i in range (n):
            if q and nums [i] >= q [-1]:
                skip = False
                while q:
                    add = q.pop ()
                    if not skip:
                        score += add
                    skip = not skip
                continue
            q.append (nums [i])
        skip = False
        while q:
            add = q.pop ()
            if not skip:
                score += add
            skip = not skip

        return score