#define CONSTRAINT 101

int minOperations (int* nums, int numsSize, int k) {
    int result = 0, map [CONSTRAINT] = {0}, i;
    for (i = 0; i < numsSize; map [nums [i++]] = 1)
        if (nums [i] < k) return -1;
    for (i = k + 1; i < CONSTRAINT; result += map [i++]);
    return result;
}