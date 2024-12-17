/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getFinalState (int* nums, int numsSize, int k, int multiplier, int* returnSize) {
    *returnSize = numsSize;
    int* result = (int*) malloc (numsSize * sizeof (int));
    
    for (int i = 0; i < numsSize; i++) {
        result [i] = nums [i];
    }
    
    for (int i = 0; i < k; ++i) {
        int minIndex = 0;
        for (int j = 1; j < numsSize; j++) {
            if (result [j] < result [minIndex]) {
                minIndex = j;
            }
        }
        result [minIndex] *= multiplier;
    }
    
    return result;
}