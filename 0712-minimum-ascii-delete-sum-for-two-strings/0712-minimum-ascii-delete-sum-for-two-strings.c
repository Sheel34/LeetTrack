int minimumDeleteSum (char* s1, char* s2) {
    int n = strlen (s1);
    int m = strlen (s2);

    int** dp = (int**) malloc ((n + 1) * sizeof (int*));
    for (int i = 0; i <= n; i++)
        dp [i] = (int*) calloc (m + 1, sizeof (int));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s1 [i] == s2 [j])
                dp [i + 1] [j + 1] = dp [i] [j] + (int) s1 [i];
            else
                dp [i + 1] [j + 1] = fmax (dp [i] [j + 1], dp [i + 1] [j]);
        }
    }

    int total = 0;
    for (int i = 0; i < n; i++) total += s1 [i];
    for (int j = 0; j < m; j++) total += s2 [j];

    int ans = total - 2 * dp [n] [m];

    for (int i = 0; i <= n; i++) free (dp [i]);
    free (dp);

    return ans;
}