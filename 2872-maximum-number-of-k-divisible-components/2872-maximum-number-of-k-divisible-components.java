class Solution {
    public int maxKDivisibleComponents (int n, int [] [] edges, int [] values, int k) {
        List <List <Integer>> adj = new ArrayList <> ();
        for (int i = 0; i < n; i++) adj.add (new ArrayList <> ());
        for (int edge [] : edges) {
            adj.get (edge [1]).add (edge [0]);
            adj.get (edge [0]).add (edge [1]);
        } 
        int res [] = new int [1];
        dfs (adj, values, 0, -1, k, res);
        return res [0];
    }
    
    private int dfs (List <List <Integer>> adj, int values [], int node, int parent, int k, int res []) {
        int sum = values [node];
        for (int temp : adj.get (node)) {
            if (temp != parent) 
                sum += dfs (adj, values, temp, node, k, res);
        }
        if (sum % k == 0) res [0] ++;
        return sum % k;
    }
}