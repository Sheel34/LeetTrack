/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

 int findSubstring (const char* str, const char* sub) {
    return strstr (str, sub) != NULL;
}

char** stringMatching (char** words, int wordsSize, int* returnSize) {
    char** ans = (char**) malloc (wordsSize * sizeof (char*));
    int ansIndex = 0;

    for (int i = 0; i < wordsSize; ++i) {
        for (int j = 0; j < wordsSize; ++j) {
            if (i != j && findSubstring (words [j], words [i])) {
                ans [ansIndex++] = words [i];
                break;
            }
        }
    }
    *returnSize = ansIndex;
    return ans;
}