class Solution {
    public int swimInWater (int [] [] grid) {
        int n = grid.length;
        int [] [] dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        boolean [] [] vis= new boolean [n] [n];
        PriorityQueue <int []> pq = new PriorityQueue <> ((a, b) -> a [0] - b [0]);
        pq.add (new int [] {grid [0] [0], 0 , 0});
        vis [0] [0]= true;
        int res = 0;
        while (!pq.isEmpty ()) {
            int [] cur= pq.poll ();
            int t = cur [0], r= cur [1], c = cur [2];
            res= Math.max (res, t);
            if (r == n - 1 && c == n - 1) return res;
            for (int [] d : dirs) {
                int nr= r + d [0], nc= c + d [1];
                if (nr >= 0 && nr < n && nc >= 0 && nc < n && !vis [nr] [nc]) {
                    vis [nr] [nc]= true;
                    pq.add (new int [] {grid [nr] [nc], nr, nc});
                }
            }
        }
        return res;
    }
}