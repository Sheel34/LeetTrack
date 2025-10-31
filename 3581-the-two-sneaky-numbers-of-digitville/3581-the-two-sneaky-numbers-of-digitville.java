class Solution {
    public int [] getSneakyNumbers (int [] nums) {
        boolean [] a = new boolean [nums.length];
        int [] ar = new int [2];
        int k = 0;
        for (int i = 0; i < nums.length; i++) {
            if (a [nums [i]]==true) ar [k++] = nums [i];
            else a [nums [i]] = true;
        }
        return ar;
    }
}