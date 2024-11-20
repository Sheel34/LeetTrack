int takeCharacters(char* s, int k) {
    int n = strlen(s);
    int a = 0, b = 0, c = 0;
    for (int i = 0; i < n; i++) 
    {
        if (s[i] == 'a') a++;
        else if (s[i] == 'b') b++;
        else if (s[i] == 'c') c++;
    }
    a -= k;
    b -= k;
    c -= k;
    if (a < 0 || b < 0 || c < 0) return -1;

    int i = 0, j = 0, max_len = 0;
    while (j < n) 
    {
        if (s[j] == 'a') a--;
        else if (s[j] == 'b') b--;
        else if (s[j] == 'c') c--;
        while (a < 0 || b < 0 || c < 0) 
        {
            if (s[i] == 'a') a++;
            else if (s[i] == 'b') b++;
            else if (s[i] == 'c') c++;
            i++;
        }
        max_len = (j - i + 1 > max_len) ? j - i + 1 : max_len;
        j++;
    }
    return n - max_len;
}