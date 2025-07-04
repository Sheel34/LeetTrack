class Solution:
    def kthCharacter (self, k : int, operations : List [int]) -> str:
        c = 0
        k -= 1
        i = 0
        while k != 0:
            c += int ((k & 1) & operations [i])
            i += 1
            k >>= 1
        return chr ((c % 26) + ord ("a"))