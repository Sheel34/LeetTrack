class Solution {
    public int [] leftmostBuildingQueries (int [] heights, int [] [] queries) {
        List <int []> que = new ArrayList <> ();
        int ind = 0;
        for (int [] x : queries) {
            int [] tmp = {Math.max (heights [x [0]], heights [x [1]]), x [0], x [1], ind};
            que.add (tmp);
            ind++;
        }
        Collections.sort (que, (a, b) -> Integer.compare (b [0], a [0]));

        List <int []> arr = new ArrayList <> ();
        int n = heights.length;
        for (int i = 0; i < n; i++) {
            int [] pair = {heights [i], i};
            arr.add (pair);
        }
        arr.sort ((a, b) -> Integer.compare (b [0], a [0]));

        TreeSet <Integer> st = new TreeSet <> ();
        int inf = 1000000000;
        st.add (inf);

        int sz = queries.length;
        int [] ans = new int [sz];
        ind = 0;

        for (int i = 0; i < sz; i++) {
            while (ind < n && arr.get (ind) [0] > que.get (i) [0]) {
                st.add (arr.get (ind) [1]);
                ind++;
            }

            int mx = Math.max (que.get (i) [1], que.get(i) [2]);
            int value = st.higher (mx); 
            if (value == inf) value = -1;
            int a = que.get (i) [1];
            int b = que.get (i) [2];
            if ((a < b && heights [a] < heights [b]) || (a > b && heights [a] > heights [b]))
                value = Math.max (a, b);
            if (que.get (i) [1] == que.get (i) [2]) value = que.get (i) [1];
            ans[que.get (i) [3]] = value;
        }

        return ans;
    }
}