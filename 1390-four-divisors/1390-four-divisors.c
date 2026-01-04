int isPrime (int x) {
    if (x < 2) return 0;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return 0;
    }
    return 1;
}

int sumOne (int n) {
    int p = (int) round (cbrt (n));
    if ((long) p * p * p == n && isPrime (p))
        return 1 + p + p * p + p * p * p;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            int a = i, b = n / i;
            if (a != b && isPrime (a) && isPrime (b))
                return 1 + a + b + n;
            return -1;
        }
    }
    return -1;
}

int sumFourDivisors (int* nums, int numsSize) {
    int res = 0;
    for (int i = 0; i < numsSize; i++) {
        int val = sumOne (nums [i]);
        if (val != -1) res += val;
    }
    return res;
}