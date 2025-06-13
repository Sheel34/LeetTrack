#pragma GCC ("03, unroll-loops")

int compare (const void* a, const void* b) {
    return *(int*) a - *(int*) b;
}

int minimizeMax(int* n, int numsSize, int p) {
    qsort (n, numsSize, sizeof (int), compare);
    int l = 0, r = n [numsSize - 1] - n [0];
    while (l < r) {
        int m = (l + r) / 2, cnt = 0;
        for (int i = 0; i + 1 < numsSize; ++i)
            if (m >= (n[i + 1] - n[i])) {
                ++cnt;
                ++i;
            }
        if (cnt >= p)
            r = m;
        else
            l = m + 1;
    }
    return l;
}