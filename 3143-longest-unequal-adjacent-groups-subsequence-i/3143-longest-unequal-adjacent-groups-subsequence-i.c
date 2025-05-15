/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** getLongestSubsequence (char** words, int wordsSize, int* groups, int groupsSize, int* returnSize) {
    char** result = (char**) calloc (wordsSize, sizeof (char*));
    *returnSize = 0;
    for (int i = 0, group_idx = -1; i < wordsSize; i++) {
        if (groups [i] == group_idx) continue;
        group_idx = groups [i];
        result [(*returnSize)] = (char*) calloc (10 + 1, sizeof (char));
        strcpy (result [(*returnSize)++], words [i]);
    }
    return result;
}