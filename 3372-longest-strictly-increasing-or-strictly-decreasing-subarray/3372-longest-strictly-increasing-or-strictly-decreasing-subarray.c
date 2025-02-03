int max (int a, int b) { return a > b ? a : b; }

int longestMonotonicSubarray (int* nums, int numsSize) {
    int ans = 1, inc = 1, dec = 1;
        for (int i = 1; i < numsSize; i++) {
            bool A = nums [i] > nums [i - 1], B = nums [i] < nums [i - 1];
            inc = A * inc + 1;
            dec = B * dec + 1;
            ans = max (ans, max (inc , dec));
        }
        return ans;
}