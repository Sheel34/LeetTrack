/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

int cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int** divideArray(int* nums, int numsSize, int k, int* returnSize, int** returnColumnSizes) {
    int* nsort = malloc(numsSize * sizeof(int));
    memcpy(nsort, nums, numsSize * sizeof(int));
    qsort(nsort, numsSize, sizeof(int), cmp);

    int rows = numsSize / 3;
    int* colSizes = malloc(rows * sizeof(int));

    int** res = malloc(rows * sizeof(int*));
    for(int i = 0, ni = 0; i < rows; i++, ni += 3)
    {
        if(nsort[ni + 2] - nsort[ni] > k)
        {
            *returnSize = 0;
            returnColumnSizes = NULL;
            return NULL;
        }

        res[i] = &nsort[ni];
        colSizes[i] = 3;
    }

    *returnSize = rows;
    *returnColumnSizes = colSizes;
    return res;
}