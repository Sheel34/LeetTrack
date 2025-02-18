char* smallestNumber (char* pattern) {
    int n = strlen (pattern);
    char* result = (char*) malloc ((n + 2) * sizeof (char));
    int index = 0;
    for (int i = 0, num = 1; i <= n; i++) {
        result [index++] = '0' + num;
        num++;
        if (i == n || pattern [i] == 'I') {
            int left = index - 1;
            int right = left;
            while (right > 0 && pattern [right - 1] == 'D')
                right--;
            while (left > right && right >= 0) {
                char temp = result [left];
                result [left] = result [right];
                result [right] = temp;
                left--;
                right++;
        }
    }
    }
    result [n + 1] = '\0';
    return result;
}