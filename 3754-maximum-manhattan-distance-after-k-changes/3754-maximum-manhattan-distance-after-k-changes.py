class Solution:
    def maxDistance(self, s: str, k: int) -> int:
        def compute(dir1, dir2, dir3, dir4, k_cnt, dist):
            dist[dir1] += 1 if k_cnt[dir1] > 0 else -1
            k_cnt[dir1] -= 1

            dist[dir2] += 1 if k_cnt[dir2] > 0 else -1
            k_cnt[dir2] -= 1

            dist[dir3] += 1
            dist[dir4] += 1

        if len(s) == k:
            return k

        mx = 0
        k_cnt = [k] * 4
        dist = [0] * 4

        for ch in s:
            if ch == 'N':
                compute(1, 3, 0, 2, k_cnt, dist)
            elif ch == 'E':
                compute(2, 3, 1, 0, k_cnt, dist)
            elif ch == 'W':
                compute(0, 1, 2, 3, k_cnt, dist)
            else:
                compute(0, 2, 1, 3, k_cnt, dist)

            mx = max(mx, max(dist))

        return mx