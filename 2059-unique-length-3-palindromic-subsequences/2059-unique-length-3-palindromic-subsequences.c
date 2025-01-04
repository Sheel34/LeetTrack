int countPalindromicSubsequence(char* s) {

    int R [26] = {0};
    int L [26] = {0};
    int result = 0;
    int len = strlen (s);
    
    for (int i = 0; i < len; i++) {
        R [s [i] - 'a']++;
    }

    bool S [26 * 26] = {false};

    for (int i = 0; i < len; i++) {
        int t = s [i] - 'a';
        R [t]--;
        for (int j = 0; j < 26; j++) {
            if (L [j] > 0 && R [j] > 0) {
                S [26 * t + j] = true;
            }
        }
        L [t]++;
    }

    for (int i = 0; i < 26 * 26; i++) {
        if (S [i]) {
            result++;
        }
    }

    return result;
}