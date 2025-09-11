int isVowel (char c) {
    switch (c) {
        case 'A': case 'E': case 'I': case 'O': case 'U':
        case 'a': case 'e': case 'i': case 'o': case 'u':
            return 1;
        default:
            return 0;
    }
}

int cmp (const void* a, const void* b) {
    return (*(char*) a - *(char*) b);
}

char* sortVowels (char* s) {
    int len = strlen (s);
    char* vowels = (char*) malloc (len);
    int v_count = 0;
    for (int i = 0; i < len; ++i)
        if (isVowel (s [i]))
            vowels [v_count++] = s [i];
    qsort (vowels, v_count, sizeof (char), cmp);
    for (int i = 0, j = 0; i < len; ++i)
        if (isVowel (s [i]))
            s [i] = vowels [j++];
    free (vowels);
    return s;
}