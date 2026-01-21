/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* minBitwiseArray (int* nums, int numsSize, int* returnSize) {
    int* answer = (int*) malloc (sizeof (int) * numsSize);
    *returnSize = numsSize;
    for (int i = 0; i < numsSize; i++) {
        int k = nums [i], n = 1, ans = -1; 
        while ((k & n) != 0) {
            ans = k - n;
            n <<= 1;
        }
        answer [i] = ans;
    }
    return answer;
}