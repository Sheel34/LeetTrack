int minMaxDifference(int num) {
    int min_v = num, max_v = num;
    for (int i = 0; i < 10; ++i) {
        int lo = 0, hi = 0, mul = 1;
        for (int n = num; n; n /= 10) {
            bool replace = n % 10 == i;
            lo += (replace ? 0 : n % 10) * mul;
            hi += (replace ? 9 : n % 10) * mul;
            mul *= 10;
        }
        min_v = fmin(min_v, lo);
        max_v = fmax(max_v, hi);
    }
    return max_v - min_v;
}