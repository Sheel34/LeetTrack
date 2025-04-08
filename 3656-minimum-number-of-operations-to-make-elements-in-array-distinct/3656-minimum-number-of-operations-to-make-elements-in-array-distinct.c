#define CONSTRAINT 101

int minimumOperations (int* nums, int numsSize) {
    int freq [CONSTRAINT] = {0};
    for (int i = numsSize - 1; i >= 0; freq [nums [i--]] = 1)
        if (freq [nums [i]]) return (i + 1) / 3 + ((i + 1) % 3 ? 1 : 0);
    return 0;
}