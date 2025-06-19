int compare (const void *a, const void* b) {
    return *(int*) a - *(int*) b;
}

int partitionArray (int* nums, int numsSize, int k) {
    qsort (nums, numsSize, sizeof (int), compare);
    int count = 0, start = 0, end = 0;
    while (end < numsSize) {
        while (end < numsSize && (nums [end] - nums [start]) <= k)
            end++;
        start = end;
        count++;
    }
    return count;
}