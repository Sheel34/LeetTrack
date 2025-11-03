class Solution {
    public int minCost (String colors, int [] neededTime) {
        int l = 0, r;
        final int n = colors.length ();
        int removes = 0, locMax = 0;
        for (r = 0; r < n;) {
            while (r < n && colors.charAt (r) == colors.charAt (l)) {
                removes += neededTime [r];
                locMax = Math.max (locMax, neededTime [r]);
                r++;
            }
            removes -= locMax;
            locMax = 0;
            l = r; 
        }
        return removes;
    }
}