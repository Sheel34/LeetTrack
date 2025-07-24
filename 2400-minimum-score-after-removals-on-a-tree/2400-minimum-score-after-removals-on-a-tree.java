class Solution {
    List<Integer>[] tree;
    int[] nums, subtreeXor, inTime, outTime, parent;
    int time = 0;
    public int minimumScore(int[] nums, int[][] edges) {
        int n = nums.length;
        this.nums = nums;

        tree = new ArrayList[n];
        for (int i = 0; i < n; i++) tree[i] = new ArrayList<>();

        for (int[] edge : edges) {
            int u = edge[0], v = edge[1];
            tree[u].add(v);
            tree[v].add(u);
        }
        subtreeXor = new int[n];
        inTime = new int[n];
        outTime = new int[n];
        parent = new int[n];
        int totalXor = dfs(0, -1); 
        int minScore = Integer.MAX_VALUE;
        for (int i = 0; i < edges.length; i++) {
            int a = getChild(edges[i][0], edges[i][1]);
            for (int j = i + 1; j < edges.length; j++) {
                int b = getChild(edges[j][0], edges[j][1]);
                int xor1, xor2, xor3;
                if (isAncestor(a, b)) {
                    xor1 = subtreeXor[b];
                    xor2 = subtreeXor[a] ^ subtreeXor[b];
                    xor3 = totalXor ^ subtreeXor[a];
                } else if (isAncestor(b, a)) {
                    xor1 = subtreeXor[a];
                    xor2 = subtreeXor[b] ^ subtreeXor[a];
                    xor3 = totalXor ^ subtreeXor[b];
                } else {
                    xor1 = subtreeXor[a];
                    xor2 = subtreeXor[b];
                    xor3 = totalXor ^ subtreeXor[a] ^ subtreeXor[b];
                }
                int maxX = Math.max(xor1, Math.max(xor2, xor3));
                int minX = Math.min(xor1, Math.min(xor2, xor3));
                minScore = Math.min(minScore, maxX - minX);
            }
        }
        return minScore;
    }

    private int dfs(int node, int par) {
        inTime[node] = time++;
        parent[node] = par;
        int xor = nums[node];

        for (int child : tree[node]) {
            if (child != par)
                xor ^= dfs(child, node);
        }
        outTime[node] = time++;
        subtreeXor[node] = xor;
        return xor;
    }

    private boolean isAncestor(int u, int v) {
        return inTime[u] <= inTime[v] && outTime[v] <= outTime[u];
    }

    private int getChild(int u, int v) {
        return parent[v] == u ? v : u;
    }
}