/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sumZero (int n, int* returnSize) {
    *returnSize = n;
    int* res = (int*) malloc (sizeof (int) * n);
    res [0] = n * (1 - n) / 2;
    for (int i = 1; i < n; i++)
        res [i] = i;
    return res; 
}