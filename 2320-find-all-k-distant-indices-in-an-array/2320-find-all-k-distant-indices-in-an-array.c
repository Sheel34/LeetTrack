/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findKDistantIndices (int* nums, int numsSize, int key, int k, int* returnSize) {
    int *arr = (int*) malloc (sizeof (int) * numsSize);
    int index = 0;

    for (int i = 0; i < numsSize; i++) {
        if (nums [i] == key) {
            int j = fmax (0, i - k);
            if (index != 0)
                j = fmax (j, arr [index - 1] + 1);
            for (; j <= fmin (i + k, numsSize - 1); j++)
                arr [index++] = j;
        }
    }
    *returnSize = index;
    return arr;
}