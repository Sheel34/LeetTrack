bool canMakeSubsequence(char* str1, char* str2) {

    int i = 0, j = 0;

    char lessChar (char ch) {
        return ch == 'a' ? 'z' : (char) (ch - 1);
    }
    
    while (i < strlen (str1) && j < strlen (str2)) {
        if (str1 [i] == lessChar (str2 [j]) || str1 [i] == str2 [j]) {
            j++;
        }
        i++;
    }

    return j == strlen (str2);
}