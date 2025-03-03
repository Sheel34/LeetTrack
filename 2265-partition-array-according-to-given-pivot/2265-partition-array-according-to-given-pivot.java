class Solution {
    public int [] pivotArray (int [] nums, int pivot) {
        int n = nums.length;
        int [] less = new int [n], high = new int [n], result = new int [n];
        int count = 0, j = 0, k = 0;
        for (int num : nums) {
            if (num < pivot) less [j++] = num;
            else if (num == pivot) count++;
            else high [k++] = num;
        }
        int index = 0;
        for (int a = 0; a < j; a++) result [index++] = less [a];
        for (int a = 0; a < count; a++) result [index++] = pivot;
        for (int a = 0; a < k; a++) result [index++] = high [a];
        return result;
    }
}