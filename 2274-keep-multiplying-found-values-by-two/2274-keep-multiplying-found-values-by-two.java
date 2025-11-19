class Solution {
    public int findFinalValue (int [] nums, int original) {
        int bits = 0;
        for (int i = 0; i < nums.length; i++) {
            if (nums [i] % original != 0) continue;
            nums [i] = nums [i] / original;
            if ((nums [i] & (nums [i] - 1)) == 0)
                bits |= nums[i];
        }
        int d = bits + 1;
        return original * (d & -d);
    }
}