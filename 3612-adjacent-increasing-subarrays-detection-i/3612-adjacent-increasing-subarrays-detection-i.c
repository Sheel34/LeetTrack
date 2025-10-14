bool hasIncreasingSubarrays (int* nums, int numsSize, int k) {
    int inc = 1, prevInc = 0, maxLen = 0;
    for (int i = 1; i < numsSize; i++) {
        if (nums [i] > nums [i - 1]) inc++;
        else {
            prevInc = inc;
            inc = 1;
        }
        int val = (inc >> 1) > (prevInc < inc ? prevInc : inc) ? (inc >> 1) : (prevInc < inc ? prevInc : inc);
        if (val > maxLen) maxLen = val;
        if (maxLen >= k) return true;
    }
    return false;
}