int findNumbers (int* nums, int numsSize) {
    int count = 0;
    for (int i = 0; i < numsSize; i++) {
        int digits = 0;
        while (nums [i] > 0) {
            digits++;
            nums [i] /= 10;
        }
        if ((digits & 1) == 0)
            count++;
    }
    return count;
}