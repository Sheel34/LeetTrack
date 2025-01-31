class Solution:
    def largestIsland (self, grid : List [List [int]]) -> int:
        n = len (grid)
        directions = [ (1,0), (-1,0), (0,1), (0,-1) ]
        key = []
        current_id = 2

        def dfs (i, j, id):
            if i < 0 or j < 0 or i >= n or j >= n or grid [i] [j] != 1:
                return 0
            grid [i] [j] = id
            count = 1
            for dx, dy in directions:
                count += dfs (i + dx, j + dy, id)
            return count

        for i in range (n):
            for j in range (n):
                if grid [i] [j] == 1:
                    size = dfs (i, j, current_id)
                    key.append (size)
                    current_id += 1

        if not key:
            return 1

        max_size = 0

        for i in range (n):
            for j in range (n):
                if grid [i] [j] == 0:
                    seen = set ()
                    current = 1
                    for dx, dy in directions:
                        ni, nj = i + dx, j + dy
                        if 0 <= ni < n and 0 <= nj < n and grid [ni] [nj] != 0:
                            island_id = grid [ni] [nj]
                            if island_id not in seen:
                                current += key [island_id - 2]
                                seen.add (island_id)
                    max_size = max (max_size, current)

        return max_size if max_size != 0 else n * n