int findMaxForm (char** strs, int strsSize, int m, int n) {
  int* dp = (int*) calloc ((m + 1) * (n + 1), sizeof (int));
    for (int i = 0; i < strsSize; ++i) {
        int zeros = 0, ones = 0;
        for (int j = 0; strs [i] [j]; ++j) {
            if (strs [i] [j] == '0') zeros++;
            else ones++;
        }
        for (int x = m; x >= zeros; --x) {
            for (int y = n; y >= ones; --y) {
                int idx = x * (n + 1) + y;
                int prev = (x - zeros) * (n + 1) + (y - ones);
                if (dp [idx] < dp [prev] + 1)
                    dp [idx] = dp [prev] + 1;
            }
        }
    }
    int result = dp [m * (n + 1) + n];
    free(dp);
    return result;  
}