/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* vowelStrings (char** words, int wordsSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {

    int* Prefix = (int*) malloc ((wordsSize + 1) * sizeof (int));
    char* vowels = "aeiou";
    Prefix [0] = 0;
    
    for (int i = 0; i < wordsSize; i++) {
        Prefix [i + 1] = Prefix [i];
        if (strchr (vowels, words [i] [0]) && strchr (vowels, words [i] [strlen (words [i]) - 1])) {
            Prefix [i + 1]++;
        }
    }

    int* result = (int*) malloc (queriesSize * sizeof (int));
    for (int i = 0; i < queriesSize; i++) {
        result [i] = Prefix [queries [i] [1] + 1] - Prefix [queries [i] [0]];
    }

    *returnSize = queriesSize;
    free (Prefix);
    return result;
}