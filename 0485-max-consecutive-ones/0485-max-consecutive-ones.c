int findMaxConsecutiveOnes(int* nums, int numsSize) {
    int count = 0, maxCount = 0;
    for (int i = 0; i < numsSize; i++) {
        count++;
        if (nums [i] == 0)
            count = 0;
        maxCount = fmax (maxCount, count);
    }
    return maxCount;
}