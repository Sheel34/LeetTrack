int repeatedNTimes(int* A, int numsSize) {
    for (int i = 0; i < numsSize - 2; i++)
    if (A[i] == A[i + 1] || A[i] == A[i + 2])
        return A[i];
    return A[numsSize - 1];
}