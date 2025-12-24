class Solution {
    public int minimumBoxes (int [] apple, int [] capacity) {
        int n = apple.length, m = capacity.length;
        int sumApples = 0, count = 0;
        for (int i = 0; i < n; i++)
            sumApples += apple [i];
        Arrays.sort (capacity);
        int right = m - 1;
        while (right >= 0) {
            sumApples -= capacity [right];
            count++;
            if (sumApples <= 0) break;
            right--;
        }
        return count;
    }
}