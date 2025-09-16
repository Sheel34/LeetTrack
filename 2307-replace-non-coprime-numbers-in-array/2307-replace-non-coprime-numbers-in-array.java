class Solution {
    public List <Integer> replaceNonCoprimes (int[] nums) {
        List <Long> merged = new ArrayList <> (); 
        for (int num : nums) {
            long current = num;
            while (!merged.isEmpty ()) {
                long last = merged.get (merged.size () - 1);
                long commonDiv = gcd (last, current);
                if (commonDiv == 1) break; 
                current = merged.remove (merged.size () - 1) * current / commonDiv;
            }
            merged.add (current);
        }
        List <Integer> result = new ArrayList <> ();
        for (long val : merged)
            result.add ((int) val);
        return result;
    }
    private long gcd (long a, long b) {
        while (b != 0) {
            long temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
}