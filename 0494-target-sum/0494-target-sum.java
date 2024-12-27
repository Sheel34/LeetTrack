class Solution {
    public int findTargetSumWays(int[] nums, int target) {
        return helper (nums, target, 0, 0);
    }
    private int helper (int [] arr, int target, int index, int sum) {
        if (index >= arr.length)
            return sum == target ? 1 : 0;
        int sub = helper (arr, target, index + 1, sum - arr [index]);
        int add = helper (arr, target, index + 1, sum + arr [index]);

        return sub + add;
    }
}