class Solution {
    public int numIslands (char [] [] grid) {
        int m = grid.length, n = grid [0].length, islands = 0;
        boolean [] [] vis = new boolean [m] [n];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (!vis [i] [j] && grid [i] [j] == '1') {
                    dfs (grid, vis, m, n, i, j);
                    islands++;
                }
            }
        }
        return islands;
    }
    private void dfs (char [] [] grid, boolean [] [] vis, int m, int n, int i, int j) {
        if (i < 0 || j < 0 || i >= m || j >= n || grid [i] [j] == '0' || vis [i] [j])
            return;
        vis [i] [j] = true;
        dfs (grid, vis, m, n, i, j - 1);
        dfs (grid, vis, m, n, i - 1, j);
        dfs (grid, vis, m, n, i, j + 1);
        dfs (grid, vis, m, n, i + 1, j);
    }
}