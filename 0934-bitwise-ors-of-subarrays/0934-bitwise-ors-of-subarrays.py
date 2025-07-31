class Solution:
    def subarrayBitwiseORs (self, arr : List [int]) -> int:
        res = set ()    
        cur = set ()   
        for x in arr:
            nxt = {x}
            for y in cur:
                nxt.add(y | x)
            res |= nxt   
            cur = nxt    
        return len(res)