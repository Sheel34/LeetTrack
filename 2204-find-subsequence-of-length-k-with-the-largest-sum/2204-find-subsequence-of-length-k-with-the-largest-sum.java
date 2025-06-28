class Item {
    int val; 
    int index;
    public Item (int val, int index) {
        this.val = val;
        this.index = index;
    }  
}

class Solution {
    public int [] maxSubsequence (int [] nums, int k) {
        PriorityQueue <Item> pq = new PriorityQueue <> ((a, b) -> a.val - b.val);
        PriorityQueue <Item> pq1 = new PriorityQueue <> ((a, b) -> a.index - b.index);
        for (int i = 0; i < nums.length; i++) {
            pq.add (new Item (nums [i], i));
            while (!pq.isEmpty () && pq.size () > k)
                pq.poll ();
        }
        while (!pq.isEmpty ())
            pq1.add (pq.poll ());
        int [] ans = new int [k];
        int p = 0;
        while (!pq1.isEmpty ())      
            ans [p++] = pq1.poll ().val;
        return ans;
    }
}