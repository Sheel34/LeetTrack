#pragma GCC optimize ("O3, unroll-loops")

int countPermutations (int* complexity, int n) {
    const int x0 = complexity [0], mod = 1e9 + 7;
    long long cnt = 1;
    int x1 = INT_MAX;
    for (int i = 1; i < n; i++) {
        x1 = fmin (x1, complexity [i]);
        cnt *= i;
        cnt %= mod;
    }
    return x0 >= x1 ? 0 : cnt;
}