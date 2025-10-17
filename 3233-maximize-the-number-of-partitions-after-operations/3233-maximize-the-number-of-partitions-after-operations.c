int maxPartitionsAfterOperations (char* s, int k) {
    if (k == 26) return 1;
    int n = strlen (s);
    int leftMask [n], leftDup [n], leftParts [n];
    int mask = 0, dup = 0, parts = 1;
    for (int i = 0; i < n; i++) {
        int bit = 1 << (s [i] - 'a');
        dup |= mask & bit;
        mask |= bit;
        if (__builtin_popcount (mask) > k) {
            mask = bit;
            dup = 0;
            parts++;
        }
        leftMask [i] = mask;
        leftDup [i] = dup;
        leftParts [i] = parts;
    }
    int result = parts;
    mask = dup = parts = 0;
    for (int i = n - 1; i >= 0; i--) {
        int bit = 1 << (s [i] - 'a');
        dup |= mask & bit;
        mask |= bit;
        int bitCount = __builtin_popcount (mask);
        if (bitCount > k) {
            mask = bit;
            dup = 0;
            parts++;
            bitCount = 1;
        }
        if (bitCount == k) {
            if ((bit & dup) && (bit & leftDup [i]) && 
                (__builtin_popcount (leftMask [i]) == k) && 
                ((leftMask [i] | mask) != 0x3FFFFFF)) {
                result = fmax (result, parts + leftParts [i] + 2);
            } else if (dup) {
                result = fmax (result, parts + leftParts [i] + 1);
            }
        }
    }
    return result;
}