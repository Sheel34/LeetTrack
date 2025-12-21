int minDeletionSize (char** strs, int strsSize) {
    int n = strsSize;
    int m = strlen (strs [0]);
    int resolved [n];
    memset (resolved, 0, sizeof (resolved));
    int unresolved = n - 1;
    int deletions = 0;
    for (int col = 0; col < m && unresolved > 0; col++) {
        int needDelete = 0;
        for (int row = 0; row < n - 1; row++) {
            if (!resolved [row] && strs [row] [col] > strs [row + 1] [col]) {
                needDelete = 1;
                break;
            }
        }
        if (needDelete) {
            deletions++;
            continue;
        }
        for (int row = 0; row < n - 1; row++) {
            if (!resolved [row] && strs [row] [col] < strs [row + 1] [col]) {
                resolved [row] = 1;
                unresolved--;
            }
        }
    }
    return deletions;
}