class Solution {
    public boolean dfs (int node, int [] visited, int [] [] graph) {
        visited [node] = 2;

        for (int it : graph [node]) {
            if (visited [it] == 0) {
                if (dfs (it, visited, graph)) {
                    return true;
                }
            } else if (visited [it] == 2) {
                return true;
            }
        }

        visited [node] = 1;
        return false;
    }
    public List <Integer> eventualSafeNodes (int [] [] graph) {
        int V = graph.length;
        int [] visited = new int [V];

        for (int i = 0; i < V; i++) {
            if (visited [i] == 0) {
                dfs (i, visited, graph);
            }
        }

        List <Integer> safeNodes = new ArrayList <> ();
        for (int i = 0; i < V; i++) {
            if (visited [i] == 1) {
                safeNodes.add (i);
            }
        }
        return safeNodes;
    }
}