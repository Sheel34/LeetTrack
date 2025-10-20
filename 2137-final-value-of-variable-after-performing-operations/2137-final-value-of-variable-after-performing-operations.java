class Solution {
    public int finalValueAfterOperations (String [] operations) {
        int x = 0;
        for (String op : operations)
            x += 44 - op.charAt (1);        
        return x;
    }
}