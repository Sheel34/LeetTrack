class Solution {
    public long countSubarrays (int [] nums, int k) {
        long count = 0, ans = 0;
        int maxN = Arrays.stream (nums).max ().getAsInt ();
        int left = 0, n = nums.length;
        for (int right = 0; right < n; right++) {
            if (nums [right] == maxN) count++;
            while (count >= k) {
                ans += n - right;
                if (nums [left] == maxN) count--;
                left++;
            }
        }
        return ans;
    }
}