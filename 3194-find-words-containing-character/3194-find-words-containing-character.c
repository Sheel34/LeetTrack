/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findWordsContaining(char** words, int wordsSize, char x, int* returnSize) {
    int* result = (int*)malloc(wordsSize * sizeof(int));
    int count = 0;
    
    for (int i = 0; i < wordsSize; i++) {
        if (strchr(words[i], x) != NULL) {
            result[count++] = i;
        }
    }
    
    *returnSize = count;
    return result;
}