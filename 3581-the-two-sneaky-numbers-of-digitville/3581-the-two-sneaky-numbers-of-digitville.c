/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getSneakyNumbers (int* nums, int numsSize, int* returnSize) {
    bool* a = (bool*) malloc (sizeof (bool) * numsSize);
    for (int i = 0; i < numsSize; i++) a [i] = false;
    int* ar = (int*) malloc (sizeof (int) * 2);
    *returnSize = 2;
    int k = 0;
    for (int i = 0; i < numsSize; i++) {
        if (a [nums [i]] == true) ar [k++] = nums [i];
        else a [nums [i]] = true;
    }
    return ar;
}