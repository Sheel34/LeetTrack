int compare (const void* a, const void* b) {
    return *(int*) a - *(int*) b;
}

int maxDistinctElements (int* nums, int numsSize, int k) {
    qsort (nums, numsSize, sizeof (int), compare);
    int ans = 0, prev = -1e9;
    for (int i = 0; i < numsSize; i++) {
        int l = fmax (nums [i] - k, prev + 1);
        if (l <= nums [i] + k) {
            prev = l, ans++;
        }
    }
    return ans;
}