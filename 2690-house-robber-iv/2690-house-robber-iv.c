bool canRob (int nums [], int numsSize, int k, int capability) {
    int count = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums [i] <= capability) {
            count++;
            i++;
        } if (count >= k) return true;
    }
    return count >= k;
}

int minCapability (int* nums, int numsSize, int k) {
    int left = INT_MAX, right = INT_MIN;
    for (int i = 0; i <numsSize; i++) {
        left = fmin (left, nums [i]);
        right = fmax (right, nums [i]);
    }
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (canRob (nums, numsSize, k, mid))
            right = mid;
        else
            left = mid + 1;
    }
    return left;
}

