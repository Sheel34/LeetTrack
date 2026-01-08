#pragma GCC optimize ("O3, unroll-loops")

int maxDotProduct (int* nums1, int n1, int* nums2, int n2) {
    if (n1 < n2)
        return maxDotProduct (nums2, n2, nums1, n1);
    int dp [2] [501];

    for (register int i = 0; i < 2; i++)
        for (register int j = 0; j <= 500; j++)
            dp [i] [j] = INT_MIN;
    int res = INT_MIN;
    for (register int i = n1 - 1; i >= 0; i--) {
        for (register int j = n2- 1; j >= 0; j--) {
            register int x = nums1 [i] * nums2 [j], tmp = dp [i & 1] [j];
            tmp = fmax (tmp, x);
            tmp = fmax (tmp, x + (i + 1 < n1 & j + 1 < n2 ? dp [(i + 1) & 1] [j + 1] : 0));
            tmp = fmax (tmp, dp [i & 1] [(j + 1)]);
            dp [i & 1] [j] = fmax (tmp, dp [(i + 1) & 1] [j]);
            res = fmax (res, dp [i & 1] [j]);
        }
    }
    return res;
}