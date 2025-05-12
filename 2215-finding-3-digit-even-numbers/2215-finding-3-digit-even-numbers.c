/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#pragma GCC optimize ("O3,unroll-loops")

int* findEvenNumbers (int* digits, int n, int* returnSize) {
    int freq [10] = {0}, cntEven = 0;
    for (int i = 0; i < n; i++) {
        const int x = digits [i];
        freq [x]++;
        cntEven += (x & 1) == 0;
    }
    *returnSize = 0;
    if (cntEven == 0) return NULL;
    int* ans = malloc (sizeof (int) * 450);
    int sz = 0;
    for (int x = 100; x <= 999; x += 2) {
        int x0 = x % 10, x1 = (x / 10) % 10, x2 = x / 100;
        freq [x0]--, freq [x1]--, freq [x2]--;
        if (freq [x0] >= 0 && freq [x1] >= 0 && freq [x2] >= 0)
            ans [sz++] = x;
        freq [x0]++, freq [x1]++, freq [x2]++;
    }
    *returnSize = sz;
    return ans;
}