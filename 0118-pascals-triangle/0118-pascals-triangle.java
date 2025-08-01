class Solution {
    public List <List <Integer>> generate (int numRows) {
        List <List <Integer>> a = new ArrayList <> ();
        for (int i = 0; i < numRows; i++) {
            List <Integer> row = new ArrayList <> (Collections.nCopies (i + 1, 1));
            for (int j = 1; j < i; j++) {
                int val = a.get (i - 1).get (j - 1) + a.get (i - 1).get (j);
                row.set (j, val);
            }
            a.add (row);
        }
        return a;
    }
}