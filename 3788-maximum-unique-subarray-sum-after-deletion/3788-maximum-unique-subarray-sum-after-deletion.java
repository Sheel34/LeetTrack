class Solution {
    public int maxSum (int [] nums) {
        int freq [] = new int [201];    
        int result = 0, maxNum = Integer.MIN_VALUE;
        for (int i = 0; i < nums.length; ++i) {
            freq [nums [i] + 100]++;
            if (nums [i] > maxNum) maxNum = nums [i];
        }
        for (int i = 0; i < 201; ++i){
            int num = i - 100;
            if (freq [i] > 0 && num > 0)
                result += num;
        }
        if (result != maxNum && result == 0)
            return maxNum;
        return result;
    }
}