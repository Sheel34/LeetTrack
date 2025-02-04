int maxAscendingSum (int* nums, int numsSize) {
    int maxSum = 0, sum = nums [0];
    for (int i = 1; i < numsSize; i++) {
        if (nums [i] > nums [i - 1]) sum += nums [i];
        else {
            maxSum = fmax (maxSum, sum);
            sum = nums [i];
        }
    }
    return fmax (maxSum, sum);
}