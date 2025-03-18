int longestNiceSubarray (int* nums, int numsSize) {
    int maxLength = 1, left = 0, usedBits = 0;
    for (int i = 0; i < numsSize; i++) {
        while ((usedBits & nums [i]) != 0) {
            usedBits ^= nums [left];
            left++;
        }
        usedBits |= nums [i];
        maxLength = fmax (maxLength, i - left + 1);
    }
    return maxLength;
}