bool check (int* nums, int numsSize) {
    int count = 0;
    for (int i = 0; i < numsSize; i++)
        if (nums [i] > nums [(i + 1) % numsSize] && ++count > 1) return false;
    return count <= 1;
}