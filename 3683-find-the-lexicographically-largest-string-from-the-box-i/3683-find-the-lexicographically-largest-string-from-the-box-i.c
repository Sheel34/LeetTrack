char* answerString(char* word, int numFriends) {
    int word_len = strlen(word);
    if (numFriends == 1) {
        char* ans = (char*)malloc(word_len + 1);
        strcpy(ans, word);
        return ans;
    }

    int len = word_len - (numFriends - 1);
    char* ans = (char*)malloc(len + 1); 

    ans[0] = '\0'; 

    for (int i = 0; i < word_len; ++i) {
        int sub_len = (word_len - i) < len ? word_len - i : len;
        char* t = (char*)malloc(sub_len + 1); 

        strncpy(t, word + i, sub_len);
        t[sub_len] = '\0'; 

        if (strcmp(ans, t) < 0) {
            free(ans);
            ans = t;
        } else {
            free(t);
        }
    }
    return ans;
}