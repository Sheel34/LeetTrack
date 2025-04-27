int countSubarrays (int* nums, int numsSize) {
    int ans = 0;
    for (int i = 0; i < numsSize; i++) {
        if (i <= numsSize - 3)
            if (nums [i] + nums [i + 2] == ((double) nums [i + 1]) / 2)
                    ans++;
    }
    return ans;
}