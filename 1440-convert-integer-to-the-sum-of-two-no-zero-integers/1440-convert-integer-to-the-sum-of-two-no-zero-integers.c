/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getNoZeroIntegers (int n, int* returnSize) {
    int* result = (int*) malloc (2 * sizeof (int));
    for (int i = 1; i < n; ++i) {
        int j = n - i;
        int valid = 1;
        int a = i, b = j;
        while (a > 0) {
            if (a % 10 == 0) {
                valid = 0;
                break;
            }
            a /= 10;
        }
        while (b > 0 && valid) {
            if (b % 10 == 0) {
                valid = 0;
                break;
            }
            b /= 10;
        }
        if (valid) {
            result [0] = i;
            result [1] = j;
            *returnSize = 2;
            return result;
        }
    }
    *returnSize = 0;
    return NULL;
}