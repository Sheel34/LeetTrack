int compare (const void* a, const void* b) {
    return *(int*) a - *(int*) b;
}

int findLHS (int* nums, int numsSize) {
    qsort (nums, numsSize, sizeof (int), compare);
    int max = 0;
    int i = 0;
    while (i < numsSize) {
        int count1 = 0, count2 = 0;
        int val = nums [i];
        while (i < numsSize && nums [i] == val) {
            count1++;
            i++;
        }
        int j = i;
        while (j < numsSize && nums [j] == val + 1) {
            count2++;
            j++;
        }
        if (count2 > 0) {
            int total = count1 + count2;
            if (total > max) {
                max = total;
            }
        }
    }
    return max;
}