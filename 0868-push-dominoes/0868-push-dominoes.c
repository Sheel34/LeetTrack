void push (char* dominoes, int start, int end, int len) {
    if (start > end)
        return;
    int left = 0,right = 0;
    if (start > 0 && dominoes [start - 1] == 'R')
        right = 1;
    if (end < len - 1 && dominoes [end + 1] == 'L')
        left = 1;
    if (start == end) {
        if (left == 1 && right == 0)
            dominoes [start] = 'L';
        if (left == 0 && right == 1)
            dominoes [start] = 'R';
    }
    else {
        int flag = 0;
        if (left == 1) {
            flag = 1;
            dominoes [end] = 'L';
            end--;
        }
        if (right == 1) {
            flag = 1;
            dominoes [start] = 'R';
            start++;
        }
        if (flag == 1)
            push (dominoes, start, end, len);
    }
    return;
}

char* pushDominoes (char* dominoes) {
    int i = 0, start, end, len = strlen (dominoes);
    while (i < len) {
        if (dominoes [i] != '.')
            i++;
        else {
            start = i;
            while (dominoes [i] == '.')
                i++;
            end = i - 1; i++;
            push (dominoes, start, end, len);
        }
    }
    return dominoes;
}