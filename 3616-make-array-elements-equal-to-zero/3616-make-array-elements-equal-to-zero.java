class Solution {
    public int countValidSelections (int [] nums) {
        int count = 0, left = 0;
        int right = Arrays.stream (nums).sum ();
        for (int i = 0; i < nums.length; i++) {
            left += nums [i];
            right -= nums [i];
            if (nums[i] != 0) continue;
            if (left == right) count += 2;
            if (Math.abs (left - right) == 1) count++;
        }
        return count;
    }
}