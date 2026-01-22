bool isSorted (int* nums, int numsSize) {
    for (int i = 1; i < numsSize; i++) {
        if (nums [i] < nums [i - 1]) return false;
    }
    return true;
}

int minimumPairRemoval (int* nums, int numsSize) {
    int ans = 0;
    while (!isSorted (nums, numsSize)) {
        ans += 1;
        int min_sum = INT_MAX, pos = -1;
        for (int i = 1; i < numsSize; i++) {
            int sum = nums [i - 1] + nums [i];
            if (sum < min_sum) {
                min_sum = sum;
                pos = i;
            }
        }
        nums [pos - 1] = min_sum;
        for (int i = pos; i < numsSize - 1; i++) nums [i] = nums [i + 1];
        numsSize--;
    }
    return ans;
}