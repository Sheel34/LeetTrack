int longestSubarray (int* nums, int numsSize) {
    if (nums == NULL || numsSize == 0)
            return 0;
    int maxVal = 0;
    for (int i = 0; i < numsSize; i++)
        if (nums [i] > maxVal)
            maxVal = nums [i];
    int maxLen = 0;
    int currentLen = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums [i] == maxVal)
            currentLen++;
        else {
            maxLen = fmax (maxLen, currentLen);
            currentLen = 0;
        }
    }
    return fmax (maxLen, currentLen);
}