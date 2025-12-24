class Solution:
    def minimumBoxes (self, apple : List [int], capacity : List [int]) -> int:
        total = sum (apple)
        capacity.sort (reverse = True)
        count = 0
        for c in capacity:
            total -= c
            count += 1
            if total <= 0: break
        return count