int dp [50] [50];
static int f (int i, int j, int v []) {
    if (dp [i] [j] != -1) return dp [i] [j];
    if (j - i <= 1) return dp [i] [j] = 0;
    if (j - i == 2) return dp [i] [j] = v [i] * v [i + 1] * v [i + 2];
    const int e = v [i] * v [j];
    int ans = INT_MAX;
    for (int k = i + 1; k < j; k++)
        ans = fmin (ans, e * v [k] + f (i, k, v) + f (k, j, v));
    return dp [i] [j] = ans;
}

int minScoreTriangulation (int* values, int valuesSize) {
    const int n = valuesSize;
    if (n == 3) return values [0] * values [1] * values [2];
    for (int i = 0; i < n; i++)
        memset (dp [i], -1, 4 * n);
    return f (0, n - 1, values);
}