int maxAdjacentDistance(int* nums, int n) {
    int ans = fabs(nums[0] - nums[n - 1]);

    for (int i = 1; i < n; i++) {
        int val = fabs(nums[i - 1] - nums[i]);
        ans = fmax(ans, val);
    }
    return ans;
}