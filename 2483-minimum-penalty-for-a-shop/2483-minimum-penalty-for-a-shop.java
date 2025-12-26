class Solution {
    public int bestClosingTime (String customers) {
        int bestTime = 0, min = 0, pre = 0;
        for (int i = 0; i < customers.length (); i++) {
            pre += (customers.charAt (i) == 'Y') ? -1 : 1;
            if (pre < min) {
                bestTime = i + 1;
                min = pre;
            }
        }
        return bestTime;
    }
}