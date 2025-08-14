class Solution:
    def largestGoodInteger (self, num : str) -> str:
        patterns = ["999","888","777","666","555","444","333","222","111","000"]
        for p in patterns:
            if p in num:
                return p
        return ""