int compare (const void* a, const void* b) {
    return *(int*) a - *(int*) b;
}

int minimumDifference(int* nums, int numsSize, int k) {
    int n = numsSize;
    qsort(nums, numsSize, sizeof (int), compare);
    int ans = nums[k - 1] - nums[0];
    for(int i = 0; i + k <= n; i ++){
        ans = fmin(ans, nums[i + k - 1] - nums[i]);
    }
    return ans;
}