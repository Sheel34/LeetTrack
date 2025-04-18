char* countAndSay (int n) {
    if (n == 1) {
        char* base = (char*) malloc (2);
        strcpy (base, "1");
        return base;
    }
    char* prev = countAndSay (n - 1);
    int len = strlen (prev);
    char* result = (char*) malloc (len * 2 + 1); 
    int resIndex = 0;
    for (int i = 0; i < len;) {
        char currentChar = prev [i];
        int count = 0;
        while (i < len && prev [i] == currentChar) {
            count++;
            i++;
        }
        result [resIndex++] = count + '0';
        result [resIndex++] = currentChar;
    }
    result [resIndex] = '\0'; 
    free (prev); 
    return result;
}