long long dp [100000];

long long dfs (int** q, int n, int i) {
    if (i >= n) return 0;
    if (dp [i] != -1) return dp [i];
    long long pt = q [i] [0];
    int skip = q [i] [1];
    dp [i] = fmax (pt + dfs (q, n, i + skip + 1), dfs (q, n, i + 1));
    return dp [i];
}

long long mostPoints (int** questions, int questionsSize, int* questionsColSize) {
    memset (dp, -1, questionsSize * sizeof (long long));
    return dfs (questions, questionsSize, 0);
}