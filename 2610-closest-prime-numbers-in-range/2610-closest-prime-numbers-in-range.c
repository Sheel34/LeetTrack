/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* closestPrimes (int left, int right, int* returnSize) {
    bool* isPrime = (bool*) malloc ((right + 1) * sizeof (bool));
    for (int i = 0; i <= right; i++) isPrime [i] = true;
    isPrime [0] = isPrime [1] = false;
    for (int i = 2; i * i <= right; i++)
        if (isPrime [i])
            for (int j = i * i; j <= right; j += i)
                isPrime [j] = false;
    int* primes = (int*) malloc ((right - left + 1) * sizeof (int));
    int count = 0;
    for (int i = left; i <= right; i++)
        if (isPrime [i]) primes [count++] = i;
    if (count < 2) {
        *returnSize = 2;
        int* res = (int*) malloc (2 * sizeof (int));
        res [0] = res [1] = -1;
        return res;
    }
    int* res = (int*) malloc (2 * sizeof (int));
    int minDiff = INT_MAX;
    for (int i = 1; i < count; i++) {
        int diff = primes [i] - primes [i - 1];
        if (diff < minDiff) {
            minDiff = diff;
            res [0] = primes [i - 1];
            res [1] = primes [i];
        }
    }
    *returnSize = 2;
    return res;
}