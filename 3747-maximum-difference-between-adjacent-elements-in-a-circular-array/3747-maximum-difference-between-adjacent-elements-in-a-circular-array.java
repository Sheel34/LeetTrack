class Solution {
    public int maxAdjacentDistance(int[] nums) {
        int n = nums.length;
        int diff = Math.abs (nums [n - 1] - nums [0]);
        for (int i = 1; i < n; i++) {
            int d = Math.abs (nums [i] - nums [i - 1]);
            diff = Math.max (diff, d);
        }
        return diff;
    }
}