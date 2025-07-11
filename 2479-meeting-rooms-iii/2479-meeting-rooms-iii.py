class Solution:
    def mostBooked(self, n: int, meetings: List[List[int]]) -> int:
        busy = [0] * n  
        count = [0] * n  

        meetings.sort()

        for start, end in meetings:
            earliest = float('inf')
            roomIndex = -1
            assigned = False

            for i in range(n):
                if busy[i] < earliest:
                    earliest = busy[i]
                    roomIndex = i
                if busy[i] <= start:
                    busy[i] = end
                    count[i] += 1
                    assigned = True
                    break

            if not assigned:
                busy[roomIndex] += end - start
                count[roomIndex] += 1

        maxCount = max(count)
        return count.index(maxCount)