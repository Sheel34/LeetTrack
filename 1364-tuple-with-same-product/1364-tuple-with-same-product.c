int tupleSameProduct (int* nums, int numsSize) {
    int *multiple = calloc (100000001, sizeof (int));
    int product = 0, result = 0;
    for (int i = 0; i < numsSize; i++) {
        for (int j = 0; j < i; j++) {
            product = nums [i] * nums [j];
            result += (multiple [product] * 8);
            multiple [product]++;
        }
    }
    free (multiple);
    return result;
}