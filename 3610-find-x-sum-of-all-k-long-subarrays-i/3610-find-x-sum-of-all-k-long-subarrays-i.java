class Pair {
    int val;
    int freq;
    public Pair (int val, int freq) {
        this.val = val;
        this.freq = freq;
    }
}

class Solution {
    public int [] findXSum (int [] nums, int k, int x) {
        int n = nums.length;
        int ans [] = new int [n - k + 1];
        for (int i = 0; i < ans.length; i++) ans [i] = calculateXSum (nums, i, i + k - 1, x);
        return ans;
    }
    public int calculateXSum (int [] nums, int start, int end, int x) {
        int ans = 0;
        int [] occurence = new int [51];
        PriorityQueue <Pair> pq = new PriorityQueue <> ((a,b) -> {
            if (a.freq == b.freq) return b.val - a.val;
            return b.freq - a.freq;
        });
        for (int i = start; i <= end; i++) occurence [nums [i]]++;
        for (int i = 1; i < 51; i++) if(occurence [i] != 0) pq.add (new Pair (i, occurence [i]));
        while (x != 0 && !pq.isEmpty ()){
            ans += pq.peek ().freq * pq.peek ().val;
            pq.poll ();
            x--;
        }
        return ans;
    }
}