class Solution:
    def leftmostBuildingQueries (self, heights: List [int], queries: List [List [int]]) -> List [int]:
        result, index = [0] * len (queries), []
        for i, q in enumerate (queries):
            a, b = sorted (q)
            if a == b or heights [a] < heights [b]:
                result [i] = b
            else:
                index.append ((a, b, i))
        j, mono = len (heights) - 1, deque()
        for a, b, i in sorted (index, key = itemgetter (1), reverse = True):
            while j > b:
                while mono and heights [mono [0]] < heights [j]:
                    mono.popleft ()
                mono.appendleft (j)
                j -= 1
            k = bisect_right (mono, heights[a], key = lambda x : heights [x])
            result [i] = -1 if k == len (mono) else mono [k]
        return result