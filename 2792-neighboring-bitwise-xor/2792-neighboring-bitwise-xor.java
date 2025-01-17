class Solution {
    public boolean doesValidArrayExist (int [] derived) {
        int n = derived.length;
        int [] org = new int [n];

        for (int i = 1; i < n; i++) {
            org [i] = derived [i - 1] ^ org [i - 1];
        }

        for (int i = 0; i < n; i++) {
            int index = (i + 1) % n;
            if (derived [i] != (org [i] ^ org [index])) return false;
        }

        return true;
    }
}