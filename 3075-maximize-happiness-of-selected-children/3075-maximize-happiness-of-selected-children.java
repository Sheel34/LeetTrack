class Solution {
    public long maximumHappinessSum (int [] happiness, int k) {
        Arrays.sort (happiness);
        for (int i = 0; i < happiness.length / 2; i++) {
            int temp = happiness [i];
            happiness [i] = happiness [happiness.length - i - 1];
            happiness [happiness.length - i - 1] = temp;
        }
        long total = 0;
        for (int i = 0; i < k; i++) {
            long curr = happiness [i] - i;
            if (curr <= 0) break;
            total += curr;
        }
        return total;
    }
}