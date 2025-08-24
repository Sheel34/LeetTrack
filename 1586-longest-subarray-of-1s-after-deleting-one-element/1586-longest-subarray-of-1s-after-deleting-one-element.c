int longestSubarray (int* nums, int numsSize) {
    int left = 0, zeros = 0, res = 0;
    for (int right = 0; right < numsSize; right++) {
        if (nums [right] == 0) zeros++;
        while (zeros > 1) {
            if (nums [left] == 0) zeros--;
            left++;
        }
        int length = right - left;
        if (length > res) res = length;
    }
    return res;
}