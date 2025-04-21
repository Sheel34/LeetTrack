int numberOfArrays (int* differences, int differencesSize, int lower, int upper) {
    long long a = 0, max = 0, min = 0;
    for (int i = 0; i < differencesSize; i++) {
        a += differences [i];
        max = fmax (max, a);
        min = fmin (min, a);
    }
    return (int) fmax (0, (upper - lower) - (max - min) + 1);
}