class Solution {
    public int [] smallestSubarrays (int [] nums) {
        int last [] = new int [32];
        for (int i = nums.length - 1; i >= 0; i--) {
            int maxIndex = i;
            for (int b = 0; b < 32; b++) {
                if ((nums [i] & (1 << b)) != 0)
                    last [b] = i;
                else
                    maxIndex = Math.max (maxIndex, last [b]);
            }
            nums [i] = maxIndex - i + 1;
        }
        return nums;
    }
}