int dfs (int* nums, int index, int currOr, int maxOr, int numsSize) {
    if (index == numsSize) return currOr == maxOr ? 1 : 0;
    int include = dfs (nums, index + 1, currOr | nums [index], maxOr, numsSize);
    int exclude = dfs (nums, index + 1, currOr, maxOr, numsSize);
    return include + exclude;
}

int countMaxOrSubsets (int* nums, int numsSize) {
    int maxOr = 0;
    for (int i = 0; i < numsSize; i++) maxOr |= nums [i];
    return dfs (nums, 0, 0, maxOr, numsSize);
}
