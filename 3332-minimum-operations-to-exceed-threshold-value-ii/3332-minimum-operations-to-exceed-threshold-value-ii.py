class Solution:
    def minOperations (self, nums : List [int], k : int) -> int:
        nums.sort ()
        b = []
        i = j = count = 0
        
        while True:
            if i < len (nums) and (j >= len (b) or nums [i] <= b [j]):
                x = nums [i]
                i += 1
            else:
                x = b [j]
                j += 1
            
            if x >= k:
                return count
            
            if i < len(nums) and (j >= len (b) or nums [i] <= b [j]):
                y = nums [i]
                i += 1
            else:
                y = b [j]
                j += 1
            
            b.append (2 * x + y)
            count += 1
        return -1