class Solution {
    public int smallestNumber (int n) {
        while ((n & (n + 1)) != 0) n |= n + 1;
        return n;
    }
}