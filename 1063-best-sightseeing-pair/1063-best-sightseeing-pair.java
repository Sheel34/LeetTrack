class Solution {
    public int maxScoreSightseeingPair (int [] values) {
        
        int ans = 0;
        int prev = values [0];

        for (int i = 1; i < values.length; i++) {
            ans = Math.max (ans, prev + values [i] - i);
            prev = Math.max (prev, values [i] + i);
        }

        return ans;
    }
}