int minZeroArray (int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize) {
    int* counts = (int*) calloc (numsSize + 1, sizeof (int));
    int k = 0, sum = 0;
    for (int i = 0; i < numsSize; i++) {
        int num = nums [i];
        while (sum + counts [i] < num) {
            if (k == queriesSize) {
                free (counts);
                return -1;
            }
            int left = queries [k] [0], right = queries [k] [1], value = queries [k] [2];
            k++;
            if (right < i) continue;
            counts [left > i ? left : i] += value;
            counts [right + 1] -= value;
        }
        sum += counts [i];
    }
    free (counts);
    return k;
}