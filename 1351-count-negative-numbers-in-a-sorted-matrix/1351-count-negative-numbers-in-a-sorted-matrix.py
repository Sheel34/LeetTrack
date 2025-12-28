class Solution:
    def countNegatives (self, grid : List [List [int]]) -> int:
        count = 0
        i, j = 0, len (grid [0]) - 1
        while i < len (grid) and j >= 0:
            if grid [i] [j] < 0:
                count += (len (grid) - i)
                j -= 1
            else: i += 1
        return count