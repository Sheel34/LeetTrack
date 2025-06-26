int longestSubsequence (char* s, int k) {
    int n = strlen (s);
    int zeros = 0;
    int ones = 0;
    long long value = 0;
    long long pow = 1;
    for (int i = 0; i < n; i++)
        if (s [i] == '0') zeros++;
    for (int i = n - 1; i >= 0; i--) {
        if (s [i] == '1') {
            if (value + pow > k) continue;
            value += pow;
            ones++;
        }
        pow <<= 1;
        if (pow > k) break;
    }
    return zeros + ones;
}