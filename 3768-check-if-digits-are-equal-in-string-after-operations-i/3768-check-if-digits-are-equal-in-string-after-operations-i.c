bool hasSameDigits (char* s) {
    for (int i = strlen (s) - 1; i >= 2; i--)
        for (int j = 0; j < i; j++)
            s [j] = (s [j] + s [j + 1]) % 10 + '0';
    return s [0] == s [1];
}