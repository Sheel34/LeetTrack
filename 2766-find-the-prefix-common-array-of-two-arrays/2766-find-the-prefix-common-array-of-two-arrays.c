/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findThePrefixCommonArray (int* A, int ASize, int* B, int BSize, int* returnSize) {
    bool *hash = calloc (ASize + 1, sizeof (bool));
    int *res = calloc (ASize, sizeof (int));
    *returnSize = ASize;
    int common = 0;

    for (int i = 0; i < ASize; i++) {
        if (hash [A [i]]) common++;
        hash [A [i]] = true;
        if (hash [B [i]]) common++;
        hash [B [i]] = true;

        res [i] = common;
    }

    return res;
}