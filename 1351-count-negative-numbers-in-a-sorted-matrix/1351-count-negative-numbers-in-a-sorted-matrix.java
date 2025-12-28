class Solution {
    public int countNegatives (int [] [] grid) {
        int count = 0;
        for (int i = 0, j = grid [0].length - 1; i < grid.length && j >= 0;) {
            if (grid [i] [j] < 0) {
                count += (grid.length - i);
                j--;
            }
            else i++;
        }
        return count;
    }
}