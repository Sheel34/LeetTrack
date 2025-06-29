const int mod = 1000000007;

int compare (const void *a, const void *b) {
    return *(int*) a - *(int*) b;
}

int numSubseq (int* nums, int numsSize, int target) {
    qsort(nums, numsSize, sizeof (int), compare);
        int n = numsSize;
        long long int p [n];
        p [0] = 1;
        for (int i = 1; i < n; i++)
            p [i] = (p [i - 1] * 2) % mod;
        int l = 0, r = n - 1;
        long long int res = 0;
        while(l <= r) {
            if (nums [l] + nums [r] <= target) {
                res = (res + (p [r - l])) % mod;
                res %= mod;
                l++;
            } else r--;
        }
        return res;
}