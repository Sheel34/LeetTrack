/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* applyOperations (int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    int *arr = (int*) calloc (*returnSize, sizeof (int));
    for (int i = 0; i < numsSize - 1; i++)
        if (nums [i] == nums [i + 1]) {
            nums [i]=nums [i] * 2;
            nums [i + 1] = 0;
        }
    int k = 0;
    for (int i = 0; i < numsSize; i++)
        if (nums [i] != 0)
            arr [k++] = nums [i];
    return arr;
}