/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* lexicalOrder(int n, int* returnSize) {
    int pos = 0, sp = n;
    int *ans = (int*) malloc(n * sizeof(int));
    int *stack = ans;
    stack[--sp] = 1;
    while (sp < n) {
        int d = stack[sp++];
        ans[pos++] = d;
        if (d % 10 < 9 && d+1 <= n) stack[--sp] = d+1;
        d *= 10;
        if (d <= n) stack[--sp] = d;
    }
    *returnSize = n;
    return ans;
}