int canBeTypedWords (char* text, char* brokenLetters) {
    bool broken [26] = {0};
    for (size_t i = 0; brokenLetters [i]; ++i) broken [brokenLetters [i] - 'a'] = true;
    int count = 0;
    const char *p = text;
    bool wordHasBroken = false;
    while (*p) {
        if (*p == ' ') {
            if (!wordHasBroken) ++count;
            wordHasBroken = false;
        } else {
            if (!wordHasBroken && broken [*p - 'a']) wordHasBroken = true;
        }
        ++p;
    }
    if (!wordHasBroken) ++count;
    return count;
}