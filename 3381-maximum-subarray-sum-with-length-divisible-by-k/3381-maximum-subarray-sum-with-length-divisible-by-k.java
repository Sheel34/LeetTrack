class Solution {
    public long maxSubarraySum (int [] nums, int k) {
        long [] min = new long [k];
        for (int i = 0; i < k - 1; i++) min [i] = Long.MAX_VALUE / 2;
        min [k - 1] = 0;
        long prefix = 0, res = Long.MIN_VALUE / 2;
        for (int i = 0; i < nums.length; i++) {
            prefix += nums [i];
            int div = i % k;
            res = Math.max (res, prefix - min [div]);
            min [div] = Math.min (prefix, min [div]);
        }
        return res;
    } 
}