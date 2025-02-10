char* clearDigits (char* s) {
    int len = strlen (s), top = -1;
    char* stack = (char*) malloc (len + 1);
    for (int i = 0; i < len; i++) {
        if (isdigit (s [i])) {
            if (top >= 0) top--;
        }
        else
            stack [++top] = s [i];
    }
    stack [++top] = '\0';
    return stack;
}