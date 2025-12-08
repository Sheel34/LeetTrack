#pragma GCC optimize ("O3, unroll-loops")

int GCD [23] [23] = {{0}};

void GCD_ () {
    if (GCD [1] [1]) return;
    const int N = 23;
    for (int i = 1; i < N; i++) {
        GCD [i] [0] = GCD [0] [i] = GCD [i] [i] = i;
        for (int j = i + 1; j < N; j++) {
            int r = j - i;
            GCD [i] [j] = GCD [j] [i] = GCD [i] [r];
        }
    }
}

int countTriples (int n) {
    GCD_ ();
    int cnt = 0;
    int nsqrt = sqrt (n);
    for (int s = 2; s <= nsqrt; s++) {
        for (int t = 1 + (s & 1); t < s; t += 2) {
            if (GCD [s] [t] != 1) continue;
            int c = s * s + t * t;
            if (c > n) break;
            int kmax = n / c;
            cnt += 2 * kmax;
        }
    }
    return cnt;
}