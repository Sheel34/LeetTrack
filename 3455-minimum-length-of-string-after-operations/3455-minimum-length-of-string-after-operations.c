int minimumLength (char* s) {
    int n = strlen (s), removableLen = 0;
    int freq [26] = {0};
    for (int i = 0; i < n; i++) {
        freq[s[i] - 'a']++;
    }

    for (int i = 0; i < 26; i++) {
        int frequency = freq [i];
        if (frequency % 2 != 0)
            removableLen += frequency - 1;
        else if (frequency != 0)
            removableLen += frequency - 2;
    }

    return n - removableLen;
}