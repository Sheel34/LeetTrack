int findFinalValue (int* nums, int numsSize, int original) {
    int i = 0;
    while (i < numsSize) {
        if (nums [i] == original) {
            original = 2 * original;
            i = 0; 
        } else i++;
    }
    return original;
}