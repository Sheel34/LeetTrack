long long zeroFilledSubarray (int* nums, int numsSize) {
    long long cnt = 0, streak = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums [i] == 0) {
            streak++;
            cnt += streak;
        } else {
            streak = 0;
        }
    }
    return cnt;
}