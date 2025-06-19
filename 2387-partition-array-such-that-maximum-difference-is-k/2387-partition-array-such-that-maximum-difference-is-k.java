class Solution {
    public int partitionArray(int[] nums, int k) {
        Arrays.sort (nums);
        int count = 0, start = 0, end = 0;
        while (end < nums.length) {
            while (end < nums.length && (nums [end] - nums [start]) <= k)
                end++;
            start = end;
            count++;
        }
        return count;
    }
}