long long minTime (int* skill, int skillSize, int* mana, int manaSize) {
    int n = skillSize, m = manaSize;
    long long done [n + 1];
    for (int i = 0; i <= n; ++i) done [i] = 0;
    for (int j = 0; j < m; ++j) {
        for (int i = 0; i < n; ++i)
            done [i + 1] = fmax (done [i + 1], done [i]) + (long long) mana [j] * skill [i];
        for (int i = n - 1; i > 0; --i)
            done [i] = done [i + 1] - (long long) mana [j] * skill [i];
    }
    return done [n];
}