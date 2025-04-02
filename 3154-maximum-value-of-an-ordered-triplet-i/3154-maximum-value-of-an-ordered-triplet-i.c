long long maximumTripletValue(int* nums, int numsSize) {
    long maxi = 0;
    for (int i = 0; i < numsSize; i++) {
        for (int k = numsSize - 1; k > i; k--) {
            int j = i + 1;
            while (j < k) {
                maxi = fmax (maxi, ((long) (nums [i] - nums [j]) * nums [k]));
                j++;
            }
        }
    }
    return maxi < 0 ? 0 : maxi;
}