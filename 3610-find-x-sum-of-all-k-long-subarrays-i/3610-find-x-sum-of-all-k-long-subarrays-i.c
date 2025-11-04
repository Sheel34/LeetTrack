/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

typedef struct {
    int num;
    int freq;
} Pair;

int cmp (const void* a, const void* b) {
    Pair* p1 = (Pair*) a;
    Pair* p2 = (Pair*) b;
    if (p2 -> freq != p1 -> freq) return p2 -> freq - p1 -> freq;
    return p2 -> num - p1 -> num;
}

int* findXSum (int* nums, int numsSize, int k, int x, int* returnSize) {
    *returnSize = numsSize - k + 1;
    int* res = (int*) malloc (sizeof (int) * (*returnSize));
    for (int i = 0; i <= numsSize - k; i++) {
        int freq [51] = {0};
        for (int j = i; j < i + k; j++) freq [nums [j]]++;
        Pair v [51];
        int cnt = 0;
        for (int num = 1; num <= 50; num++) {
            if (freq [num] > 0) {
                v [cnt].num = num;
                v [cnt].freq = freq [num];
                cnt++;
            }
        }
        qsort (v, cnt, sizeof (Pair), cmp);
        int sum = 0;
        for (int j = 0; j < cnt && j < x; j++)
            sum += v [j].num * v [j].freq;
        res [i] = sum;
    }
    return res;
}