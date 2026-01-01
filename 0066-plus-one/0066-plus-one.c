/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* plusOne (int* digits, int digitsSize, int* returnSize) {
    int* res = (int*) calloc ((digitsSize + 1), sizeof (int));
    for(int i = 0; i < digitsSize; i++) res [i] = digits [i];
    for(int i = digitsSize - 1; i >= 0; i--) {
        if(res [i] != 9) {
            res [i] += 1;
            *returnSize = digitsSize;
            return res;
        } else res [i] = 0;
    }
    res [0] = 1;
    *returnSize = digitsSize+1;
    return res;
}