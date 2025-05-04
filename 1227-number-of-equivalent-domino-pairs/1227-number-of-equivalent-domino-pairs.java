class Solution {
    public int numEquivDominoPairs (int [] [] dominoes) {
        int [] map = new int [100];
        int count = 0;
        for (int [] pair : dominoes) {
            int u = pair [0];
            int v = pair [1];
            int num = (u > v) ? v * 10 + u : u * 10 + v;
            count += map [num];
            map [num]++;
        }
        return count;
    }
}