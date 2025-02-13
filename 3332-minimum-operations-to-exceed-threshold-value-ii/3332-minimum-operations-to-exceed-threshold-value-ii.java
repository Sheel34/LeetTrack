class Solution {
    public int minOperations (int [] nums, int k) {
        Arrays.sort (nums);
        List <Integer> b = new ArrayList <> ();
        for (int i = 0, j = 0, count = 0, x, y; ; ++count) {
            if (i < nums.length && (j >= b.size () || nums [i] <= b.get (j))) x = nums [i++];
            else x = b.get (j++);
            if (x >= k) return count;
            if (i < nums.length && (j >= b.size () || nums [i] <= b.get (j))) y = nums [i++];
            else y = b.get (j++);
            long t = 2L * x + y;
            b.add (t < k ? (int) t : k);
    }
}
}