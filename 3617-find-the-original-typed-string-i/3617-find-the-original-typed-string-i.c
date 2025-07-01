int possibleStringCount (char* word) {
    int count = strlen (word);
    for (int i = 1; i < strlen (word); i++) 
        if (word [i] != word [i - 1]) count--;
    return count;
}