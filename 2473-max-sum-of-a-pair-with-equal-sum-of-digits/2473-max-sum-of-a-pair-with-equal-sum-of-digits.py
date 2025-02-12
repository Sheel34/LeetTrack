class Solution:
    def maximumSum (self, nums : List [int]) -> int:
        mp = defaultdict (list)
        
        for num in nums:
            digit_sum = sum (int (d) for d in str (num))
            heapq.heappush (mp [digit_sum], -num)
        
        ans = -1
        for values in mp.values ():
            if len (values) > 1:
                max1 = -heapq.heappop (values)
                max2 = -heapq.heappop (values)
                ans = max (ans, max1 + max2)
                
        return ans