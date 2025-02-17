int numTilePossibilities (char* tiles) {
    int counts [26] = {0};
    int len = strlen (tiles);
    int fac [len + 1];
    fac [0] = 1;
    for (int i = 1; i <= len; i++) {
        fac [i] = i * fac [i - 1];
    }
    for (int i = 0; tiles [i] != '\0'; i++) {
        counts [tiles [i] - 'A']++;
    }
    int lengthcounts [len + 1];
    memset (lengthcounts, 0, sizeof (lengthcounts));
    lengthcounts [0] = 1;
    for (int i = 0; i < 26; i++) {
        if (counts [i] > 0) {
            int temp [len + 1];
            memset (temp, 0, sizeof (temp));
            for (int j = 0; j <= len && lengthcounts [j] > 0; j++) {
                for (int k = 1; k <= counts [i]; k++) {
                    int totallength = j + k;
                    temp [totallength] += lengthcounts [j] * fac [totallength] / (fac [k] * fac [j]);
                }
            }
            for (int j = 0; j <= len; j++) {
                lengthcounts [j] += temp [j];
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= len; i++) {
        ans += lengthcounts [i];
    }
    return ans;
}