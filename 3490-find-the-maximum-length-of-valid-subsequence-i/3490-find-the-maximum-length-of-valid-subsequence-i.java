class Solution {
    public int maximumLength (int [] nums) {
        if (nums.length == 2) return 2;
        boolean z = nums [0] % 2 == 0;
        int len [] = new int [3];
        len [0] = z ? 0 : 1; len [1] = z ? 1 : 0; len [2] = 1;
        for (int i = 1; i < nums.length; i++) {
            boolean x = nums [i] % 2 == 0;
            len [x ? 1 : 0]++;
            if (x != z) {
                len [2]++;
                z = !z;
            }
        }
        return Math.max (len [0], Math.max (len [1], len [2]));
    }
}