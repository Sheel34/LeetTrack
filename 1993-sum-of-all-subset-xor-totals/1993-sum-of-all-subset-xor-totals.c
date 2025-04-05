int subsetXORSum (int* nums, int numsSize) {
    int total = 0;
    for (int i = 0; i < numsSize; i++)
        total |= nums [i];
    return total * (1 << (numsSize - 1));
}