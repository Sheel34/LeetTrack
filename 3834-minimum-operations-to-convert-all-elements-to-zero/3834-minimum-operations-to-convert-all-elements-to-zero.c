int minOperations (int* nums, int numsSize) {
    int* s = (int*) malloc (sizeof (int) * numsSize);
    if (!s) return 0;
    int top = 0, res = 0;
    for (int i = 0; i < numsSize; ++i) {
        int a = nums [i];
        while (top > 0 && s [top - 1] > a) --top;
        if (a == 0) continue;
        if (top == 0 || s [top - 1] < a) {
            res++;
            s [top++] = a;
        }
    }
    free (s);
    return res;
}