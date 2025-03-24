class Solution:
    def countDays (self, days : int, meetings : List [List [int]]) -> int:
        meetings.sort ()
        prevEnd = 0
        for start, end in meetings:
            start = max (start, prevEnd + 1)
            length = end - start + 1
            days -= max (length, 0)
            prevEnd = max (prevEnd, end)

        return days