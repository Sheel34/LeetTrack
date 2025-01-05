char* shiftingLetters (char* s, int** shifts, int shiftsSize, int* shiftsColSize) {
    int n = strlen (s);
    int shift [n + 1];
    memset (shift, 0, sizeof (shift));

    for (int i = 0; i < shiftsSize; ++i) {
        int start = shifts [i] [0], end = shifts [i] [1], direction = shifts [i] [2];
        shift [start] += (direction == 1 ? 1 : -1);
        if (end + 1 < n) shift [end + 1] -= (direction == 1 ? 1 : -1);
    }

    int currentShift = 0;
    for (int i = 0; i < n; ++i) {
        currentShift += shift [i];
        shift [i] = currentShift;
    }

    for (int i = 0; i < n; ++i) {
        int netShift = (shift [i] % 26 + 26) % 26;
        s [i] = 'a' + (s [i] - 'a' + netShift) % 26;
    }

    return s;
}