class Solution:
    def countCompleteComponents (self, n : int, edges : List [List [int]]) -> int:
        graph = defaultdict (list)
        for a, b in edges:
            graph [a].append (b)
            graph [b].append (a)
        visited = set ()
        count = 0
        def dfs (node, component):
            component.add (node)
            visited.add (node)
            for neighbor in graph [node]:
                if neighbor not in visited:
                    dfs (neighbor, component)
        for i in range (n):
            if i not in visited:
                component = set ()
                dfs (i, component)
                if all (len (graph [node]) == len (component) - 1 for node in component):
                    count += 1
        return count