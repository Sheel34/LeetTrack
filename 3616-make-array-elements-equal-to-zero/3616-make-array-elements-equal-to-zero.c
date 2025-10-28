int countValidSelections (int* nums, int numsSize) {
    int count = 0, left = 0, right = 0;
    for (int i = 0; i < numsSize; i++) right += nums [i];
    for (int i = 0; i < numsSize; i++) {
        left += nums [i];
        right -= nums [i];
        if (nums [i] != 0) continue;
        if (left == right) count += 2;
        if (abs (left - right) == 1) count++;
    }
    return count;
}