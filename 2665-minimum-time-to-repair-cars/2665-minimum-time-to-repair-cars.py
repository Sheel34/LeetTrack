class Solution:
    def repairCars (self, ranks : List [int], cars : int) -> int:
        l, r = 1, int (1e14)
        while l < r:
            mid = (l + r) // 2
            if self.time_is_suff (ranks, cars, mid):
                r = mid
            else:
                l = mid + 1
        return l
    def time_is_suff (self, ranks, cars, min_given):
        cars_done = 0
        for r in ranks:
            c2 = min_given // r
            c = int (math.sqrt (c2)) 
            cars_done += c
        return cars_done >= cars