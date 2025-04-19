int compare (const void* a, const void* b) {
    return *(int*) a - *(int*) b;
}

int lowerBound (int* nums, int numsSize, int start, int target) {
    int low = start, high = numsSize;
    while (low < high) {
        int mid = (low + high) / 2;
        if (nums [mid] < target) low = mid + 1;
        else high = mid;
    }
    return low;
}

int upperBound (int* nums, int numsSize, int start, int target) {
    int low = start, high = numsSize;
    while (low < high) {
        int mid = (low + high) / 2;
        if (nums [mid] <= target) low = mid + 1;
        else high = mid;
    }
    return low;
}

long long countFairPairs (int* nums, int numsSize, int lower, int upper) {
    qsort (nums, numsSize, sizeof (int), compare);
    long long count = 0;
    for (int i = 0; i < numsSize; i++) {
        int left = lowerBound (nums, numsSize, i + 1, lower - nums [i]);
        int right = upperBound (nums, numsSize, i + 1, upper - nums [i]);
        count += right - left;
    }
    return count;
}