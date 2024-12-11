int maximumBeauty (int* nums, int numsSize, int k) {
    
    int maxValue = 0;

    for (int i = 0; i < numsSize; i++) {
        if (nums [i] > maxValue) {
            maxValue = nums [i];
        }
    }

    int rangeSize = maxValue + 10;
    int* range = (int*) calloc (rangeSize, sizeof (int));

    for (int i = 0; i < numsSize; i++) {
        int left = (nums [i] - k > 0) ? nums [i] - k : 0;
        int right = (nums [i] + k < maxValue) ? nums [i] + k + 1 : maxValue + 1;
        range [left]++;
        if (right < rangeSize) {
            range [right]--;
        }
    }

    int result = range [0];
    for (int i = 1; i < rangeSize; i++) {
        range [i] += range [i - 1];
        if (range [i] > result) {
            result = range [i];
        }
    }

    free (range);
    return result;
}