long long countBadPairs (int* nums, int numsSize) {
    int i, *check = (int*) malloc (sizeof (int) * numsSize);
    for (i = 0; i < numsSize; i++) check[i] = nums [i], nums [i] -= i;

    struct hash {
        int num, count;
        UT_hash_handle hh;
    } *hashTable = NULL, *item;

    long long result = 0;
    for (i = numsSize - 1; i >= 0; i--) {
        HASH_FIND_INT (hashTable, & (int) {check [i] - i}, item);

        if (!item) {
            item = (struct hash*) malloc (sizeof (struct hash));
            item -> num = nums [i], item -> count = 1;
            HASH_ADD_INT (hashTable, num, item);
            
            result += numsSize - i - 1;
        }
        else result += (numsSize - i - 1) - item -> count++;
    }

    HASH_CLEAR (hh, hashTable);
    free (check);
    return result;
    
}