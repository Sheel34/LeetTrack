char nextChar (char c) {
    return (c == 'z') ? 'a' : (c + 1);
}

char kthCharacter (int k) {
    char str[512];
    int len=0;
    str[len++] = 'a';
    while (len < k) {
        int current_len = len;
        for (int i = 0; i < current_len; i++)
            str [len++] = nextChar (str [i]);
    }
    return str [k - 1];
}