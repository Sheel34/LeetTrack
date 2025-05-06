/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* buildArray (int* nums, int numsSize, int* returnSize) {
    int* result = (int*) malloc (sizeof (int) * numsSize);
    *returnSize = numsSize;
    for (int i = 0; i < numsSize; i++)
        result [i] = nums [nums [i]];
    free (nums);
    return result;
}