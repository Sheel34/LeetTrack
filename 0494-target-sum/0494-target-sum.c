int helper (int arr [], int arrSize, int target, int index, int sum) {
    if (index >= arrSize)
        return sum == target ? 1 : 0;
    int sub = helper (arr, arrSize, target, index + 1, sum - arr [index]);
    int add = helper (arr, arrSize, target, index + 1, sum + arr [index]);

    return sub + add;
}

int findTargetSumWays(int* nums, int numsSize, int target) {
    return helper (nums, numsSize, target, 0, 0);
}