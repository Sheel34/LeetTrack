int cmp (const void *a, const void *b) {
    return (*(int*) a - *(int*) b);
}

int minOperations (int* nums, int numsSize, int k) {
    qsort (nums, numsSize, sizeof (int), cmp);
    int *b = (int*) malloc (numsSize * sizeof (int));
    for (int i = 0, j = 0, g = 0, count = 0, x, y; ; ++count) {
        if (i < numsSize && (j >= g || nums [i] <= b [j])) x = nums [i++];
        else x = b [j++];
        if (x >= k) {
            free (b);
            return count;
        }
        if (i < numsSize && (j >= g || nums [i] <= b [j])) y = nums [i++];
        else y = b [j++];
        long t = 2L * x + y;
        b [g++] = (t < k) ? (int) t : k;
    }
    free (b);
    return -1;
}