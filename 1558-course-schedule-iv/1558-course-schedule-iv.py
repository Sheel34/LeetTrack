class Solution:
    def dfs (self, node, adj, visited, prerequisites, start):
        visited [node] = True

        if start != -1:
            prerequisites.add ((start, node))

        for neighbor in adj [node]:
            if not visited [neighbor]:
                self.dfs (neighbor, adj, visited, prerequisites, start)

    def checkIfPrerequisite (self, numCourses : int, prerequisites : List [List [int]], queries : List [List [int]]) -> List [bool]:

        adj = [[] for _ in range (numCourses)]
        for u, v in prerequisites:
            adj [u].append (v)

        prerequisites = set ()
        for i in range (numCourses):
            visited = [False] * numCourses
            self.dfs (i, adj, visited, prerequisites, i)

        return [tuple (query) in prerequisites for query in queries]