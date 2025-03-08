int minimumRecolors (char* blocks, int k) {
    int blackCount = 0, ans = INT_MAX;
    for (int i = 0; i < strlen (blocks); i++) {
        if (i - k >= 0 && blocks [i - k] == 'B') blackCount--;
        if (blocks [i] == 'B') blackCount++;
        ans = fmin (ans, k - blackCount);
    }
    return ans;
}