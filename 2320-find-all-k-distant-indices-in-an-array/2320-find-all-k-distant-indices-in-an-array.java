class Solution {
    public List <Integer> findKDistantIndices (int [] nums, int key, int k) {
        int v [] = new int [nums.length + 1];
        List <Integer> ans = new ArrayList <> ();
        for (int i = 0; i < nums.length; i++) {
            if (nums [i] == key) {
                int start = Math.max (0, i - k);
                int end = Math.min (nums.length, i + k + 1);
                v [start]++;
                v [end]--;
            }
        }
        int sum = 0;
        for (int i = 0; i <= nums.length; i++) {
            sum += v [i];
            if (sum > 0) ans.add (i);
        }
        return ans;
    }
}