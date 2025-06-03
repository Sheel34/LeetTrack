class Solution:
    def maxCandies(self, status: List[int], candies: List[int], keys: List[List[int]], containedBoxes: List[List[int]], initialBoxes: List[int]) -> int:
        n = len(status)
        canOpen = [False] * n
        hasBox = [False] * n
        visited = [False] * n
        queue = []

        for i in initialBoxes:
            hasBox[i] = True
            if status[i] == 1:
                canOpen[i] = True
                queue.append(i)

        for i in range(n):
            if status[i] == 1:
                canOpen[i] = True

        total = 0

        while queue:
            i = queue.pop()
            if visited[i]:
                continue
            visited[i] = True
            total += candies[i]

            for k in keys[i]:
                if not canOpen[k]:
                    canOpen[k] = True
                    if hasBox[k] and not visited[k]:
                        queue.append(k)

            for j in containedBoxes[i]:
                hasBox[j] = True
                if canOpen[j] and not visited[j]:
                    queue.append(j)

        return total