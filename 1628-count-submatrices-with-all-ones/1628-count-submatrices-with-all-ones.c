int numSubmat (int** mat, int r, int* cArr) {
    int c = cArr [0], ans = 0;
    int* h = calloc (c, sizeof (int));
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) h [j] = mat [i] [j] ? h [j] + 1 : 0;
        int* sum = calloc (c, sizeof (int));
        int* st = malloc (c * sizeof (int)), top = -1;
        for (int j = 0; j < c; j++) {
            while (top >= 0 && h [st [top]] >= h [j]) top--;
            if (top >= 0) {
                int p = st [top];
                sum [j] = sum [p] + h [j] * (j - p);
            } else
                sum [j] = h [j] * (j + 1);
            st [++top] = j;
            ans += sum [j];
        }
        free (sum);
        free (st);
    }
    free (h);
    return ans;
}