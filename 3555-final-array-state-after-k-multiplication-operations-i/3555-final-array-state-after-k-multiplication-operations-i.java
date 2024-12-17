class Solution {
    public int [] getFinalState (int [] nums, int k, int multiplier) {
        for (int i = 0; i < k; i++) {
            int index = getIndex (nums);
            nums [index] *= multiplier;
        }
        return nums;
    }

    private int getIndex (int [] array) {
        int min = Integer.MAX_VALUE;
        int index = 0;
        for (int i = 0; i < array.length; i++) {
            if (array [i] < min) {
                min = array [i];
                index = i;
            }
        }
        return index;
    }
}