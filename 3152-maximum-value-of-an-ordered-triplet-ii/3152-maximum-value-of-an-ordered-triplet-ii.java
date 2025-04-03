class Solution {
    public long maximumTripletValue (int [] nums) {
    long maxVal = 0, maxI = 0, maxIJDiff = 0;
    for (int k = 2; k < nums.length; k++) {
        if (nums [k - 2] > maxI)
            maxI = nums [k - 2];
        if (maxI - nums [k - 1] > maxIJDiff)
            maxIJDiff = maxI - nums [k - 1];
        if (maxIJDiff * nums [k] > maxVal)
            maxVal = maxIJDiff * nums [k];
    }
    return maxVal;
    }
}