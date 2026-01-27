class Solution:
    def minCost(self, n: int, edges: List[List[int]]) -> int:
        adj = defaultdict(list)
        for u, v, w in edges:
            adj[u].append((v, w))
            adj[v].append((u, 2 * w))  
        dist = [math.inf] * n
        dist[0] = 0
        heap = [(0, 0)]
        while heap:
            d, u = heapq.heappop(heap)
            if u == n - 1:  
                return d
            if d != dist[u]:  
                continue
            for v, w in adj[u]:
                if dist[u] + w < dist[v]: 
                    dist[v] = dist[u] + w
                    heapq.heappush(heap, (dist[v], v))
        return -1