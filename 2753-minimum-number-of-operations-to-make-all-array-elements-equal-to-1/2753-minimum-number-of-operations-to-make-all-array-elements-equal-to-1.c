int __gcd (int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int minOperations (int* nums, int numsSize) {
    int res = INT_MAX, cnt1 = 0;
    for (int i = 0; i < numsSize; ++i)
        cnt1 += (nums [i] == 1);
    if (cnt1) return numsSize - cnt1;
    for (int i = 0; i < numsSize; ++i) {
        int g = nums [i];
        for (int j = i + 1; j < numsSize; ++j) {
            g = __gcd (g, nums [j]);
            if (g == 1) {
                res = fmin (res, j - i + numsSize - 1);
                break;
            }
        }
    }
    return res == INT_MAX ? -1 : res;
}