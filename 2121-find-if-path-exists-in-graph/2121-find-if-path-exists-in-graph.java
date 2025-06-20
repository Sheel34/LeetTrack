class Solution {
    public boolean validPath(int n, int[][] edges, int source, int destination) {
        if (source == destination) return true;
        List <List <Integer>> gra = new ArrayList <> ();
        for (int i = 0; i < n; i++)
            gra.add (new ArrayList <> ());
        for (int [] edge : edges) {
            int u = edge [0];
            int v = edge [1];
            gra.get (u).add (v);
            gra.get (v).add (u);
        }
        boolean vis [] = new boolean [n];
        return dfs (gra, source, destination, vis);
    }
    boolean dfs (List <List <Integer>> gra, int s, int d, boolean vis []) {
        if (s == d) return true;
        vis [s] = true;
        for (int x : gra.get (s))
            if (!vis [x] && dfs (gra, x, d, vis)) return true;
        return false;
    }
}