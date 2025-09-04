class Solution {
    public int findClosest (int x, int y, int z) {
        return Math.abs (x - z) == Math.abs (y - z) ? 0 : Math.abs (x - z) < Math.abs (y - z) ? 1 : 2;
    }
}