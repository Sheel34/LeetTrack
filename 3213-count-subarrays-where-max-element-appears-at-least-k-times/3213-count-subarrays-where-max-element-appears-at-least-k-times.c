long long countSubarrays (int* nums, int numsSize, int k) {
    int max = 0;
    for (int i = 0; i < numsSize; i++)
        if (nums [i] > max)
            max = nums [i];
    long long count = 0, l = 0, maxFound = 0;
    for (int r = 0; r < numsSize; ++r) {
        if (nums [r] == max) maxFound++;
        while (maxFound == k) {
            count += numsSize - r;
            if (nums [l] == max) maxFound--;
            l++;
        }
    }
    return count;
}