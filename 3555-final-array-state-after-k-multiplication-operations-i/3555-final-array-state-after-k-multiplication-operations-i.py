class Solution:
    def getFinalState(self, nums: List[int], k: int, multiplier: int) -> List[int]:
        for _ in range (k):
            i = self.get_index (nums)
            nums [i] *= multiplier
        return nums

    def get_index (self, array):
        min_val = float ('inf')
        index = 0
        for i in range (len (array)):
            if array [i] < min_val:
                min_val = array [i]
                index = i
        return index