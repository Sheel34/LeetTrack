int findSmallestInteger (int* nums, int numsSize, int value) {
    long long x, res = 0;
    int rem [value];
    for (int i = 0; i < value; i++)
        rem [i] = 0;
    for (int i = 0; i < numsSize; i++) {
        x = ((nums [i] % value) + value) % value;
        rem [x]++;
    }
    while (rem [res % value]--) res++;
    return res;
}