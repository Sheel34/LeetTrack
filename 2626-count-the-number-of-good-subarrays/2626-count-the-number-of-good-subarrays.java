class Solution {
    public long countGood (int [] nums, int k) {
        Map <Integer, Integer> freq = new HashMap <> ();
        long ans = 0;
        long pairs = 0;
        int left = 0;
        for (int right = 0; right < nums.length; right++) {
            int val = nums [right];
            pairs += freq.getOrDefault (val, 0);
            freq.put (val, freq.getOrDefault (val, 0) + 1);
            while (pairs >= k) {
                ans += nums.length - right;
                int out = nums [left++];
                freq.put (out, freq.get (out) - 1);
                pairs -= freq.get (out);
            }
        }
        return ans;
    }
}