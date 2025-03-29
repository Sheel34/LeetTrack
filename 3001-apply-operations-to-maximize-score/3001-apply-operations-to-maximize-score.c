#define MOD 1000000007

int* global_nums;

void computePrimeScore (int* primeScore, int upper) {
    memset (primeScore, 0, upper * sizeof (int));
    for (int i = 2; i < upper; i++)
        if (primeScore [i] == 0)
            for (int j = i; j < upper; j += i)
                primeScore [j] += 1;
}

long long modPow (long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int compare (const void* a, const void* b) {
    return global_nums [* (int*)b] - global_nums [* (int*)a];
}

long long maximumScore (int* nums, int n, int k) {
    int upper = 0;
    for (int i = 0; i < n; i++)
        if (nums [i] > upper) upper = nums [i];
    upper++;
    int* primeScore = (int*) malloc (upper * sizeof (int));
    computePrimeScore (primeScore, upper);
    int* nextGreaterElement = (int*) malloc (n * sizeof (int));
    int* prevGreaterOrEqualElement = (int*) malloc (n * sizeof (int));
    int* stack = (int*) malloc (n * sizeof (int));
    int top = -1;
    for (int i = 0; i < n; i++) {
        while (top >= 0 && primeScore [nums [i]] > primeScore [nums [stack [top]]])
            top--;
        prevGreaterOrEqualElement [i] = (top >= 0) ? stack [top] : -1;
        stack [++top] = i;
    }
    top = -1;
    for (int i = n - 1; i >= 0; i--) {
        while (top >= 0 && primeScore [nums [i]] >= primeScore [nums [stack [top]]])
            top--;
        nextGreaterElement [i] = (top >= 0) ? stack [top] : n;
        stack [++top] = i;
    }
    int* sorted_indices = (int*) malloc (n * sizeof (int));
    for (int i = 0; i < n; i++)
        sorted_indices [i] = i;
    global_nums = nums;
    qsort (sorted_indices, n, sizeof (int), compare);
    long long res = 1;
    for (int i = 0; i < n && k > 0; i++) {
        int idx = sorted_indices [i];
        int num = nums [idx];
        long long operations = (long long) (idx - prevGreaterOrEqualElement [idx]) * (nextGreaterElement [idx] - idx);
        if (operations > k) operations = k;
        res = (res * modPow (num, operations, MOD)) % MOD;
        k -= operations;
        if (k == 0) break;
    }
    free (primeScore);
    free (nextGreaterElement);
    free (prevGreaterOrEqualElement);
    free (stack);
    free (sorted_indices);
    return res;
}