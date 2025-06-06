char get_min_char(const int* const count) {
    for (int i = 0; i < 26; i++) {
        if (count[i]) return i + 'a';
    }
    return 'a';
}

char* robotWithString(char* s) {
    const int n = strlen(s);
    int count[26] = {0};
    for (int i = 0; i < n; i++) {
        count[s[i] - 'a']++;
    }

    char stack[n];
    memset(stack, 0, sizeof(stack));
    int top = -1;  // size = top + 1

    char* result = (char*)calloc(n + 1, sizeof(char));
    int returnSize = 0;

    for (int i = 0; i < n; i++) {
        stack[++top] = s[i];
        count[s[i] - 'a']--;

        const char minChar = get_min_char(count);
        while (top + 1 > 0 && stack[top] <= minChar) {
            result[returnSize++] = stack[top--];
        } 
    }

    while (top + 1 > 0) {
        result[returnSize++] = stack[top--];
    }
    result[returnSize] = '\0';
    return result;
}