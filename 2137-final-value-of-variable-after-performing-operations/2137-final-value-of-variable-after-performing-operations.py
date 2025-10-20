class Solution:
    def finalValueAfterOperations (self, ops : List [str]) -> int:
        return sum (44 - ord (op [1]) for op in ops)