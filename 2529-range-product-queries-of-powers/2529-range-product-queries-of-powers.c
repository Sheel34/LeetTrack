/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#define MOD 1000000007

int* productQueries (int n, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    int pow [33], ns = 0, mask = 1, ps = 0;
    while (n > 0) {
        if (n & mask) {
            pow [ns++] = ps;
            n = n & ~mask;
        }
        mask <<= 1;
        ++ps;
    }
    int prods [ns] [ns];
    for (int i = 0; i < ns; ++i) {
        long long res = 1;
        for (int j = i; j < ns; ++j) {
            res = (res << pow [j]) % MOD;
            prods [i] [j] = res;
        }
    }
    int *ans = (int*) malloc (queriesSize * sizeof (int));
    for (int i = 0; i < queriesSize; ++i)
        ans [i] = prods [queries [i] [0]] [queries [i] [1]];
    *returnSize = queriesSize;
    return ans;
}