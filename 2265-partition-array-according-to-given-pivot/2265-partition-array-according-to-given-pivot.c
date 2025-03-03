/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* pivotArray (int* nums, int numsSize, int pivot, int* returnSize) {
    int* less = (int*) malloc (numsSize * sizeof (int));
    int* high = (int*) malloc (numsSize * sizeof (int));
    int* result = (int*) malloc (numsSize * sizeof (int));
    int count = 0, j = 0, k = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums [i] < pivot) less [j++] = nums [i];
        else if (nums [i] == pivot) count++;
        else high [k++] = nums [i];
    }
    int index = 0;
    for (int a = 0; a < j; a++) result [index++] = less [a];
    for (int a = 0; a < count; a++) result [index++] = pivot;
    for (int a = 0; a < k; a++) result [index++] = high [a];
    *returnSize = numsSize;
    free (less); free (high);
    return result;
}