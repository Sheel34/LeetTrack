int maximumSum (int* nums, int numsSize) {
    int mp [82];
    memset (mp, -1, sizeof (mp));
    int ans = -1;
    for (int i = 0; i < numsSize; i++) {
        int sumDigits = 0, temp = nums [i];
        while (temp) sumDigits += temp % 10, temp /= 10;
        if (mp [sumDigits] != -1)
            ans = fmax (ans, nums [i] + mp [sumDigits]);
        mp [sumDigits] = fmax (mp [sumDigits], nums [i]);
    }
    return ans;
}