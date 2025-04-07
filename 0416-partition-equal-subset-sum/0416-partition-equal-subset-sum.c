bool memo (int* nums, int** dp, int sum, int index, int n) {
    if (sum == 0)
        return true;
    if (index >= n)
        return false;
    if (dp [index] [sum] != -1)
        return dp [index] [sum];
    bool pick = false, no_pick = false;
    if (nums [index] <= sum)
        pick = memo (nums, dp, sum - nums [index], index + 1, n);
    no_pick = memo (nums, dp, sum, index + 1, n);
    return dp [index] [sum] = (pick || no_pick);
}

bool canPartition (int* nums, int numsSize) {
    int sum = 0;
    for (int i = 0; i < numsSize; i++)
        sum += nums [i];
    if (sum & 1)
        return false;
    int** dp = (int**) malloc (sizeof (int*) * numsSize);
    for (int i = 0; i < numsSize; ++i) {
        dp [i] = (int*) malloc (sizeof (int) * ((sum >> 1) + 1));
        for (int j = 0; j < ((sum >> 1) + 1); ++j)
            dp [i] [j] = -1;
    }
    return memo (nums, dp, sum >> 1, 0, numsSize);
}