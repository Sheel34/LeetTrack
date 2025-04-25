class Solution {
    public long countInterestingSubarrays (List <Integer> nums, int modulo, int k) {
        long total = 0;
        Map <Integer, Integer> map = new HashMap <> ();
        map.put (0, 1);
        int count = 0;
        for (int num : nums) {
            if (num % modulo == k) count++;
            int remainder = (count - k) % modulo;
            if (remainder < 0) remainder += modulo;
            total += map.getOrDefault (remainder, 0);
            map.put (count % modulo, map.getOrDefault (count % modulo, 0) + 1);
        }
        return total;
    }
}