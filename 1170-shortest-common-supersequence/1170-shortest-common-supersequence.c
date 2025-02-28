char* lcs (char* A, char* B) {
    int m = strlen (A), n = strlen (B);
    int dp [m + 1] [n + 1];
    memset (dp, 0, sizeof (dp));
    
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            if (A[i - 1] == B[j - 1])
                dp [i] [j] = dp [i - 1] [j - 1] + 1;
            else
                dp [i] [j] = (dp [i - 1] [j] > dp [i] [j - 1]) ? dp [i - 1] [j] : dp [i] [j - 1];
    int len = dp [m] [n];
    char* lcs_str = (char*) malloc ((len + 1) * sizeof (char));
    lcs_str [len] = '\0';
    int i = m, j = n, index = len - 1;
    while (i > 0 && j > 0) {
        if (A  [i - 1] == B [j - 1]){
            lcs_str [index--] = A [i - 1];
            i--, j--;
        } else if (dp [i - 1] [j] > dp [i] [j - 1])
            i--;
        else
            j--;
    }
    return lcs_str;
}

char* shortestCommonSupersequence (char* str1, char* str2) {
    char* lcs_str = lcs (str1, str2);
    int len1 = strlen (str1), len2 = strlen (str2), len_lcs = strlen (lcs_str);
    char* result = (char*) malloc ((len1 + len2 + 1) * sizeof (char));
    int i = 0, j = 0, k = 0;
    for (int x = 0; x < len_lcs; x++) {
        while (str1 [i] != lcs_str [x]) result [k++] = str1 [i++];
        while (str2 [j] != lcs_str [x]) result [k++] = str2 [j++];
        result [k++] = lcs_str [x];
        i++, j++;
    }
    
    while (i < len1) result [k++] = str1 [i++];
    while (j < len2) result [k++] = str2 [j++];
    result [k] = '\0';
    
    free (lcs_str);
    return result;
}