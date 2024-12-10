int helper (const char* s, int n, int x) {
    int count [26] = {0};
    int p = 0;

    for (int i = 0; i < n; i++) {
        while (s [p] != s [i]) p++;
        if (i - p + 1 >= x) count [s [i] - 'a']++;
        if (count [s [i] - 'a'] > 2) return 1;
    }

    return 0;
}

int maximumLength (char* s) {
    int n = strlen (s);
    int l = 1, r = n;

    if (!helper (s, n, l)) return -1;

    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (helper (s, n, mid)) l = mid;
        else r = mid;
    }

    return l;
}

