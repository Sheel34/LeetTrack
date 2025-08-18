bool judgePoint24 (int* cards, int cardsSize) {
    double nums [4];
    for (int i = 0; i < cardsSize; i++) nums [i] = (double) cards [i];
    bool dfs (double* arr, int n) {
        if (n == 1) return fabs (arr [0] - 24.0) < 1e-6;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                double next [4];
                int idx = 0;
                for (int k = 0; k < n; k++) if (k != i && k != j) next [idx++] = arr [k];
                double a = arr [i], b = arr [j], cand [6];
                int cnt = 0;
                cand [cnt++] = a + b;
                cand [cnt++] = a - b;
                cand [cnt++] = b - a;
                cand [cnt++] = a * b;
                if (fabs (b) > 1e-6) cand [cnt++] = a / b;
                if (fabs (a) > 1e-6) cand [cnt++] = b / a;
                for (int c = 0; c < cnt; c++) {
                    next [idx] = cand [c];
                    if (dfs (next, idx + 1)) return true;
                }
            }
        }
        return false;
    }
    return dfs (nums, cardsSize);
}