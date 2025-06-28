/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
struct node {
    int ind;
    int val;
};

int compareByVal (const void *a, const void *b) {
    const struct node *elemA = (const struct node *) a;
    const struct node *elemB = (const struct node *) b;
    return elemA -> val - elemB -> val;
}

int compareByInd (const void *a, const void *b) {
    const struct node *elemA = (const struct node *) a;
    const struct node *elemB = (const struct node *) b;
    return elemA -> ind - elemB -> ind;
}

int* maxSubsequence (int* nums, int numsSize, int k, int* returnSize) {
    struct node*arr = (struct node*) malloc (sizeof (struct node) * numsSize);
    struct node*arr2 = (struct node*) malloc (sizeof (struct node) * k);
    for (int i = 0; i < numsSize; i++) {
        arr [i].ind = i;
        arr [i].val = nums [i];
    }
    qsort (arr, numsSize, sizeof (struct node), compareByVal);
    *returnSize = k;
    int* res = (int*) malloc (sizeof (int) * k);
    int ind = 0;
    for (int i = numsSize - k; i < numsSize; i++) {
        (arr2 [ind]).val = (arr [i]).val;
        arr2 [ind++].ind = arr [i].ind;

    }
    qsort (arr2, k, sizeof (struct node), compareByInd);
    ind = 0;
    for (int i = 0; i < k; i++)
        res [ind++] = arr2 [i].val;
    return res;
}