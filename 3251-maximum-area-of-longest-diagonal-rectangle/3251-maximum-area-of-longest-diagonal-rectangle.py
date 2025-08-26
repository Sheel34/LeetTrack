class Solution:
    def areaOfMaxDiagonal (self, dimensions : List [List [int]]) -> int:
        max_area, max_diag = 0, 0
        for i in range (len (dimensions)):
            l = dimensions [i] [0]
            w = dimensions [i] [1]
            curr_diag = l * l + w * w
            if curr_diag > max_diag or (curr_diag == max_diag and l * w > max_area):
                max_area = l * w
                max_diag = curr_diag
        return max_area