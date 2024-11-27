class Solution:
    def bfs (self, start, end, n, graph):
        dist = [float ('inf')] * n
        dist [start] = 0
        q = deque ([start])

        while q:
            curr = q.popleft ()
            for u in graph [curr]:
                if dist [u] > dist [curr] + 1:
                    dist [u] = dist [curr] + 1
                    q.append (u)

        return dist [end]

    def shortestDistanceAfterQueries (self, n: int, queries: List[List[int]]) -> List[int]:
        answer = []
        graph = [[] for _ in range (n)]

        for i in range (n - 1):
            graph [i].append (i + 1)

        for u, v in queries:
            graph [u].append (v)
            answer.append (self.bfs (0, n - 1, n, graph))

        return answer