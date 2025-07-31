class Solution {
    public int subarrayBitwiseORs (int [] arr) {
        Set <Integer> res = new HashSet <> ();
        Set <Integer> cur = new HashSet <> ();
        for (int x : arr) {
            Set <Integer> nxt = new HashSet <> ();
            nxt.add (x);
            for (int v : cur)
                nxt.add (v | x);
            res.addAll (nxt);
            cur = nxt;
        }
        return res.size ();
    }
}