/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#define START_SIZE 8
#define ALPHA_LEN 26

int* partitionLabels (char* s, int* returnSize) {
    int *result = malloc (START_SIZE * sizeof (int)), memSize = START_SIZE, lastIndex [ALPHA_LEN], len = 0, i, j, k; *returnSize = 0;
    for (char *c = s; *c != '\0'; c++) { lastIndex [*c - 'a'] = len++; }
    for (i = 1, j = 0, k = lastIndex [s [0] - 'a']; i < len; ) {
        if (i <= k) { k = k >= lastIndex [s [i] - 'a'] ? k : lastIndex [s [i] - 'a']; i++; continue; }
        if (*returnSize >= memSize) { result = realloc (result, (memSize *= 2) * sizeof (int)); }
        result [(*returnSize)++] = i - j; j = i; k = lastIndex [s [i] - 'a']; i++;
    }
    if (*returnSize >= memSize) { result = realloc (result, (memSize *= 2) * sizeof (int)); }
    result [(*returnSize)++] = i - j;
    return result;
}