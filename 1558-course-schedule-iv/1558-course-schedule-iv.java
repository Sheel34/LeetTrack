class Solution {
    public List <Boolean> checkIfPrerequisite (int numCourses, int [] [] prerequisites, int [] [] queries) {
        List <Integer> [] adj = new ArrayList [numCourses];
        boolean [] [] prereq = new boolean [numCourses] [numCourses];
        int [] inDegree = new int [numCourses];
        
        for (int i = 0; i < numCourses; i++) {
            adj [i] = new ArrayList <> ();
        }
        
        for (int[] edge : prerequisites) {
            int a = edge [0], b = edge [1];
            adj [a].add (b);
            prereq [b] [a] = true;
            inDegree [b]++;
        }
        
        Queue <Integer> q = new LinkedList <> ();
        for (int i = 0; i < numCourses; i++) {
            if (inDegree [i] == 0) q.add (i);
        }
        
        while (!q.isEmpty ()) {
            int u = q.poll ();
            for (int v : adj [u]) {
                for (int i = 0; i < numCourses; i++) {
                    if (prereq [u] [i]) prereq [v] [i] = true;
                }
                if (--inDegree [v] == 0) q.add (v);
            }
        }
        
        List <Boolean> ans = new ArrayList <> ();
        for (int [] query : queries) {
            int u = query [0], v = query [1];
            ans.add (prereq [v] [u]);
        }
        return ans;
    }
}