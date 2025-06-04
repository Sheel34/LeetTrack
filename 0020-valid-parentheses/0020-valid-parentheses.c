bool isValid (char* s) {
    if ((strlen (s) & 1) == 1)
        return false;
    char stk [10001];
    int size = 0;
    int top = -1;
    for (int i = 0; i < strlen (s); i++) {
        if (s [i] == '(' || s [i] == '{' || s [i] == '[') {
            stk [++top] = s [i];
            size++;
        }
        else {
            if (size == 0)
                return false;
            if (((s [i] == ')') && (stk [top] != '(') || (s [i] == '}') && (stk [top] != '{') || (s [i] == ']') && (stk [top] != '[')))
                return false;
            else {
                stk [top--];
                size--;
            }
        }
    } 
    return size == 0;
}