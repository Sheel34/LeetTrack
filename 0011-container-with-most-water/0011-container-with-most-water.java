class Solution {
    public int maxArea (int [] height) {
        int r = 0;
        for (int i = 0, j = height.length - 1; i != j; ) {
            r = Math.max (r, Math.min (height [i], height [j]) * (j - i));
            if (height [i] < height [j])  ++i; else --j;
        }
        return r;
    }
}