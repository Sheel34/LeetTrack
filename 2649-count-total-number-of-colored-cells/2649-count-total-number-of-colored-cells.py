class Solution:
    def coloredCells (self, n : int) -> int:
        result = 1
        i = 0
        while i < n:
            result = result + (4 * i)
            i += 1
        return (result)