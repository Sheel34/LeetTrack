/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#pragma GCC optimize ("O3, unroll-loops")

bool* prefixesDivBy5 (int* nums, int numsSize, int* returnSize) {
    bool* ans = (bool*) malloc (sizeof (bool) * numsSize);
    int msb = 0;
    for (int i = 0; i < numsSize; i++) {
        msb = ((msb << 1) + nums [i]);
        msb -= (-(msb >= 5) & 5); 
        ans [i] = msb == 0;
    }
    *returnSize = numsSize;
    return ans;
}