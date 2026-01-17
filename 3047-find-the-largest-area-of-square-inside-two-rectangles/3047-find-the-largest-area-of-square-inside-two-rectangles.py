class Solution:
    def largestSquareArea (self, bottomLeft : List [List [int]], topRight : List [List [int]]) -> int:
        maxSide = 0
        n = len (bottomLeft)
        for i in range (n):
            for j in range (i + 1, n):
                x1 = max (bottomLeft [i] [0], bottomLeft [j] [0])
                y1 = max (bottomLeft [i] [1], bottomLeft [j] [1])
                x2 = min (topRight [i] [0], topRight [j] [0])
                y2 = min (topRight [i] [1], topRight [j] [1])
                width = x2 - x1
                height = y2 - y1
                if width > 0 and height > 0:
                    side = min (width, height)
                    maxSide = max (maxSide, side)
        return maxSide * maxSide