class Solution {
    public int helper (String w1, String w2, int i, int j, int dp [] []) {
        if (i == w1.length ()) return w2.length () - j;
        if (j == w2.length ()) return w1.length () - i;
        if (dp [i] [j] != -1) return dp [i] [j];
        int ans = 0;
        if (w1.charAt (i) == w2.charAt (j)) ans = helper (w1, w2, i + 1, j + 1, dp);
        else {
            int insert = 1 + helper (w1, w2, i, j + 1, dp);
            int delete = 1 + helper (w1, w2, i + 1, j, dp);
            int replace = 1 + helper (w1, w2, i + 1, j + 1, dp);
            ans = Math.min (insert, Math.min (delete, replace));
        }
        dp [i] [j] = ans;
        return dp [i] [j];
    }
    public int minDistance (String word1, String word2) {
        int n = word1.length (), m = word2.length ();
        int dp [] [] = new int [n] [m];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                dp [i] [j] = -1;
        return helper (word1, word2, 0, 0, dp);
    }
}