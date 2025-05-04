class Solution:
    def numEquivDominoPairs (self, dominoes : List [List [int]]) -> int:
        hash = [0] * 100
        count = 0
        for d in dominoes:
            u, v = d [0], d [1]
            num = v * 10 + u if u > v else u * 10 + v
            count += hash [num]
            hash [num] += 1
        return count