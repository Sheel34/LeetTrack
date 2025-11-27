long long maxSubarraySum (int* nums, int numsSize, int k) {
    long long* min = malloc (sizeof (long long) * k);
    for (int i = 0; i < k - 1; i++) min [i] = LLONG_MAX / 2;
    min [k - 1] = 0;
    long long prefix = 0, res = LLONG_MIN;
    for (int i = 0; i < numsSize; i++) {
        prefix += nums [i];
        int d = i % k;
        res = fmax (res, prefix - min [d]);
        min [d] = fmin (min [d], prefix);
    }
    return res;
}