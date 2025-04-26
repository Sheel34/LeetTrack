long long countSubarrays (int* nums, int numsSize, int minK, int maxK) {
    int pMin = -1, pMax = -1, bad = -1;
        long long ans = 0;
        for (int i = 0; i < numsSize; ++i) {
            if (nums [i] == minK) pMin = i;
            if (nums [i] == maxK) pMax = i;
            if (nums [i] < minK || nums [i] > maxK) bad = i;
            if (pMin != -1 && pMax != -1) {
                ans += fmax (0, fmin (pMin, pMax) - bad);
            }
        }
        return ans;
}