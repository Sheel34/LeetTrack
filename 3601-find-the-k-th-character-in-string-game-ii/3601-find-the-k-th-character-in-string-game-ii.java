class Solution {
    public char kthCharacter (long k, int [] operations) {
        int c = 0; k--;
        for (int i = 0; k != 0; i++, k >>= 1) c += ((int) (k & 1) & operations [i]);
        return (char) ((c % 26) + 'a');
    }
}