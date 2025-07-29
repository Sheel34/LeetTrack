/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* smallestSubarrays (int* nums, int numsSize, int* returnSize) {
    int last [32] = {0};
    for (int i = numsSize - 1; i >= 0; i--){
        int maxIndex = i;
        for (int b = 0; b < 32; b++){
            if (nums [i] & (1L << b))
                last [b] = i;
            else
                maxIndex = fmax (maxIndex, last[b]);
        }
        nums [i] = maxIndex - i + 1;
    }
    *returnSize = numsSize;
    return nums;
}