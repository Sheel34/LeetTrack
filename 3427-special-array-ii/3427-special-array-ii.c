/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
bool* isArraySpecial (int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    
    bool* result = (bool*) malloc (queriesSize * sizeof (bool));
    *returnSize = queriesSize;

    int* prefix = (int*) malloc (numsSize * sizeof (int));
    prefix [0] = 0;

    for (int i = 1; i < numsSize; i++) {
        prefix [i] = prefix [i - 1];
        if ((nums [i - 1] % 2 == 0 && nums [i] % 2 == 0) || (nums [i - 1] % 2 != 0 && nums [i] % 2 != 0)) {
            prefix [i]++;
        }
    }

    for (int i = 0; i < queriesSize; i++) {
        int left = queries [i] [0];
        int right = queries [i] [1];
        int specialCount = prefix [right] - (left > 0 ? prefix [left] : 0);
        result [i] = (specialCount == 0);
    }

    free (prefix);

    return result;
}