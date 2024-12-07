class Solution {
    public int minimumSize (int [] nums, int maxOperations) {

        int low = 1, high = Arrays.stream (nums).max ().getAsInt ();
        while (low < high) {
            int mid = (low + high) / 2;
            int ops = 0;
            for (int n : nums) {
                ops += (n - 1) / mid;
            }
            if (ops <= maxOperations) high = mid;
            else low = mid + 1;
        }
        return high;
    }
}