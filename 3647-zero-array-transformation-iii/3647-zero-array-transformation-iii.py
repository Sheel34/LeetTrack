class Solution:
    def maxRemoval(self, A: List[int], queries: List[List[int]]) -> int:
        queries = sorted(queries)[::-1]
        ava = SortedList()
        cur = SortedList()
        for i in range(len(A)):
            while queries and queries[-1][0] <= i:
                ava.add(queries.pop()[1])
            while cur and cur[0] < i:
                cur.pop(0)
            while A[i] > len(cur):
                if not ava or ava[-1] < i:
                    return -1
                cur.add(ava.pop())
        return len(ava)