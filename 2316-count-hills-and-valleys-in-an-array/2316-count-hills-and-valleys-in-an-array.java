class Solution {
    public int countHillValley (int [] nums) {
        int count = 0, prev = nums [0];
        int diff [] = new int [2], i = 0;
        while (i < nums.length) {
            while (i < nums.length && prev == nums [i]) i += 1;
            if (i == nums.length) break;
            int bigger;
            if (nums [i] > prev) bigger = 1;
            else bigger = 0;
            diff [bigger] = 1;
            count += ((diff [bigger] == 1) && (diff [1 - bigger] == 1)) ? 1 : 0;
            diff [1 - bigger] = 0;
            prev = nums [i];
            i++;
        }
        return count;
    }
}