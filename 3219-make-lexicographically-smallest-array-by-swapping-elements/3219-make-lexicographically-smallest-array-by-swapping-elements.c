/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int cmp (const void *a, const void *b) {
    int *arr1 = (int *) a;
    int *arr2 = (int *) b;
    return (arr1 [0] - arr2 [0]);
}

int cmp2 (const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}

int* lexicographicallySmallestArray (int* nums, int numsSize, int limit, int* returnSize) {
    int *ret = (int *) malloc (sizeof (int) * numsSize);
    *returnSize = numsSize;
    int cpy [numsSize] [2];

    for (int i = 0; i < numsSize; i++) {
        cpy [i] [0] = nums [i];
        cpy [i] [1] = i;
    }

    qsort (cpy, numsSize, sizeof (cpy [0]), cmp);

    int indices [numsSize];

    for (int i = 0; i < numsSize;) {
        int size = 0;
        int prev = cpy [i] [0];
        while (i < numsSize && cpy [i] [0] <= (prev + limit)) {
            indices [size++] = cpy [i] [1];
            prev = cpy [i] [0];
            i++;
        }

        qsort (indices, size, sizeof (int), cmp2);
        
        for (int j = 0, k = i - size; j < size; j++, k++) {
            ret [indices [j]] = cpy [k] [0];
        }
    }
    return ret;
}