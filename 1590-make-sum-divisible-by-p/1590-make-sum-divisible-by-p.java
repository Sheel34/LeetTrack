class Solution {
    public int minSubarray (int [] nums, int p) {
        long sum = 0;
        for (int i = 0; i < nums.length; i++) sum += nums [i];
        if (sum % p == 0) return 0;
        long target = sum % p;
        Map <Integer, Integer> map = new HashMap <> ();
        map.put (0, -1);
        long prefix = 0;
        int res = nums.length;
        for (int i = 0; i < nums.length; i++) {
            prefix = (prefix + nums [i]) % p;
            int val = (int) ((prefix - target + p) % p);
            if (map.containsKey (val)) res = Math.min (res, i - map.get (val));
            map.put ((int) prefix, i);
        }
        return res == nums.length ? -1 : res;
    }
}