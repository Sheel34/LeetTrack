class Solution {
    private final int [] dx = {-1, 0, 1, 0};
    private final int [] dy = {0, 1, 0, -1};
    public int trapRainWater (int [] [] heightMap) {
        if (heightMap == null || heightMap.length == 0 || heightMap [0].length == 0) 
            return 0;
            
        int m = heightMap.length;
        int n = heightMap [0].length;
        
        PriorityQueue <int []> pq = new PriorityQueue <> ((a, b) -> a [0] - b [0]);
        boolean [] [] visited = new boolean [m] [n];
        
        for (int j = 0; j < n; j++) {
            pq.offer (new int [] {heightMap [0] [j], 0, j});
            pq.offer (new int [] {heightMap [m - 1] [j], m - 1, j});
            visited [0] [j] = visited [m - 1] [j] = true;
        }
        
        for (int i = 1; i < m - 1; i++) {
            pq.offer (new int [] {heightMap [i] [0], i, 0});
            pq.offer (new int [] {heightMap [i] [n - 1], i, n - 1});
            visited [i] [0] = visited [i] [n - 1] = true;
        }
        
        int water = 0;
        while (!pq.isEmpty ()) {
            int [] curr = pq.poll ();
            int height = curr [0], row = curr [1], col = curr [2];
            
            for (int k = 0; k < 4; k++) {
                int newRow = row + dx [k];
                int newCol = col + dy [k];
                
                if (newRow < 0 || newRow >= m || newCol < 0 || newCol >= n || 
                    visited [newRow] [newCol]) continue;
                    
                if (heightMap [newRow] [newCol] < height) {
                    water += height - heightMap [newRow] [newCol];
                    pq.offer (new int [] {height, newRow, newCol});
                } else {
                    pq.offer (new int [] {heightMap [newRow] [newCol], newRow, newCol});
                }
                visited [newRow] [newCol] = true;
            }
        }
        return water;
    }
}