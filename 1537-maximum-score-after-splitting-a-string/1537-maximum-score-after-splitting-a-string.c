int maxScore(char* s) {
    int totalZeros = 0, zeros = 0, ans = -1, n = strlen (s);
    for (int i = 0; i < n; i++) {
        if (s [i] == '0') totalZeros++;
    }
    for (int i = 1; i < n; i++) {
        if (s [i - 1] == '0') {
            zeros++;
            totalZeros--;
        }
        int ones = n - totalZeros - i;
        if (ans < zeros + ones) ans = zeros + ones;
    }
    return ans;
}