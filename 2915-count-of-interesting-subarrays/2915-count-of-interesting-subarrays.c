long long countInterestingSubarrays (int* nums, int numsSize, int modulo, int k) {
    long long ans = 0;
    int count = 0;
    int *rmdMap = (int*) calloc (modulo, sizeof (int));
    rmdMap [0] = 1;
    for (int i = 0; i < numsSize; ++i) {
        count += (nums [i] % modulo == k);
        int current_remainder = count % modulo;
        int target = (current_remainder - k + modulo) % modulo;
        ans += rmdMap [target];
        rmdMap [current_remainder]++;
    }
    free (rmdMap);
    return ans;
}