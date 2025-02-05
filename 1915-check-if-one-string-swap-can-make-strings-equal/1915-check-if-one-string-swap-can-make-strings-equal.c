bool areAlmostEqual (char* s1, char* s2) {
    int i = -1, j = -1;
    int count = 0;
    for (int k = 0; k < strlen (s1); k++) {
        if (s1 [k] != s2 [k]) {
            count++;
            if (i == -1) i = k;
            else if (j == -1) j = k;
        }
    }
    if (count == 0) return true;
    else if (count == 2 && s1 [i] == s2 [j] && s1 [j] == s2 [i]) {
        return true;
    }
    return false;
}