int isPrefixOfWord(char* sentence, char* searchWord) {

    char sentenceCopy [1000];
    strcpy (sentenceCopy, sentence); // Copy sentence to tokenize
    char* token = strtok (sentenceCopy, " ");
    int index = 1;

    while (token != NULL) {
        if (strncmp (token, searchWord, strlen (searchWord)) == 0)
            return index;

        token = strtok (NULL, " ");
        index++;
    }
    return -1;
}