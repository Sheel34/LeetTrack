/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int* minOperations (char* boxes, int* returnSize) {
    int n = strlen (boxes);
    int* distances = (int*) malloc (n * sizeof (int));

    int prefixCount = 0;
    int prefixSum = 0;

    for (int i = 0; i < n; i++) {
        distances [i] = prefixCount * i - prefixSum;
        if (boxes [i] == '1') {
            ++prefixCount;
            prefixSum += i;
        }
    }

    int suffixCount = 0;
    int suffixSum = 0;

    for (int i = n - 1; i >= 0; i--) {
        distances [i] += suffixSum - suffixCount * i;
        if (boxes [i] == '1') {
            ++suffixCount;
            suffixSum += i;
        }
    }

    *returnSize = n;
    return distances;
}