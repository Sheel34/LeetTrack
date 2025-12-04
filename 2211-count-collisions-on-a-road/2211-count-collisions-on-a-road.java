class Solution {
    public int countCollisions (String dir) {
        final int n = dir.length ();
        if (n == 1) return 0;
        int l = 0, r = n - 1;
        while (l < r && dir.charAt (l) == 'L') l++;
        while (l < r && dir.charAt (r) == 'R') r--;
        if (l >= r) return 0;
        int col = 0;
        for (; l <= r; l++)
           col += (dir.charAt (l) != 'S' ? 1 : 0);
        return col;  
    }
}