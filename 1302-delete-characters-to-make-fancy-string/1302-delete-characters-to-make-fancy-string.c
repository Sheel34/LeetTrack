char* makeFancyString (char* s) {
    int n = strlen (s);
    if (n == 0) return "";
    char* result = (char*) malloc ((n + 1) * sizeof (char));
    int resIndex = 0;
    int count = 1;
    result [resIndex++] = s [0];
    for (int i = 1; i < n; i++) {
        if (s [i] == s [i - 1])
            count++;
        else
            count = 1;
        if (count < 3)
            result [resIndex++] = s [i];
    }
    result [resIndex] = '\0';
    return result;
}