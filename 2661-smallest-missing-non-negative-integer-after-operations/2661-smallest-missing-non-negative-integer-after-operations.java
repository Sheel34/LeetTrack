class Solution {
    public int findSmallestInteger (int [] nums, int value) {
        int res = 0;
        int [] rem = new int [value];
        for (int x : nums) {
            int r = ((x % value) + value) % value;
            rem [r]++;
        }
        while (rem [res % value]-- > 0) res++;
        return res;
    }
}