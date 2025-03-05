class Solution {
    public long coloredCells (int n) {
        long result = 1;
        int i = 0;
        while (i < n) {
            result = result + (4 * i);
            i++;
        }
        return result;
    }
}