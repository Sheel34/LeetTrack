int compare (const void* a, const void* b) {
    return *(int*) a - *(int*) b;
}

int maxLen (int* Bars, int BarsSize) {
    int count = 2, length = 2;
    for (int i = 1; i < BarsSize; i++) {
        if (Bars [i] - Bars [i - 1] == 1) count++;
        else count = 2;
        length = fmax (length, count);
    }
    return length;
}

int maximizeSquareHoleArea (int n, int m, int* hBars, int hBarsSize, int* vBars, int vBarsSize) {
    qsort (hBars, hBarsSize, sizeof (int), compare);
    qsort (vBars, vBarsSize, sizeof (int), compare);
    int side = fmin (maxLen (hBars, hBarsSize), maxLen (vBars, vBarsSize));
    return side * side;
}