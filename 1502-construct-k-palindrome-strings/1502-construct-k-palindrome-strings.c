bool canConstruct (char* s, int k) {
    int length = strlen (s);
    if (length < k)
        return false;

    int freq [26] = {0};
    
    for (int i = 0; s [i] != '\0'; i++) {
        freq [s [i] - 'a']++;
    }

    int odds = 0;
    for (int i = 0; i < 26; i++) {
        if (freq [i] % 2 != 0)
            odds++;
    }

    return odds <= k;
}