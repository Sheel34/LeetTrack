class Solution:
    def maxValue(self, events: List[List[int]], k: int) -> int:
        events.sort(key=lambda e: e[0])
        starts = [e[0] for e in events]
        n = len(events)
        next_idx = [0] * n
        for i in range(n):
            end_i = events[i][1]
            next_idx[i] = bisect_right(starts, end_i)

        prev = [0] * (n + 1)
        for i in range(n - 1, -1, -1):
            prev[i] = max(prev[i + 1], events[i][2])

        res = prev[0]
        for _ in range(2, k + 1):
            curr = [0] * (n + 1)
            for i in range(n - 1, -1, -1):
                take = events[i][2]
                j = next_idx[i]
                if j <= n:
                    take += prev[j]
                curr[i] = max(curr[i + 1], take)
            res = max(res, curr[0])
            prev = curr

        return res