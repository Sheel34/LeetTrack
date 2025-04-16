typedef struct {
    int key;
    int count;
    UT_hash_handle hh;
} HashEntry;


long long countGood (int* nums, int numsSize, int k) {
    int left = 0;
    long long result = 0;
    long long totalPairs = 0;
    HashEntry *map = NULL;
    for (int right = 0; right < numsSize; right++) {
        int num = nums [right];
        HashEntry *entry;
        HASH_FIND_INT (map, &num, entry);
        if (entry == NULL) {
            entry = malloc (sizeof (HashEntry));
            entry -> key = num;
            entry -> count = 0;
            HASH_ADD_INT (map, key, entry);
        }
        totalPairs += entry -> count;
        entry -> count++;
        while (totalPairs >= k) {
            result += (numsSize - right);
            int l_num = nums [left];
            HashEntry *l_entry;
            HASH_FIND_INT (map, &l_num, l_entry);
            if (l_entry) {
                l_entry -> count--;
                totalPairs -= l_entry -> count;
                if (l_entry -> count == 0) {
                    HASH_DEL (map, l_entry);
                    free (l_entry);
                }
            }
            left++;
        }
    }
    return result;
}