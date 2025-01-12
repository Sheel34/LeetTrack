bool canBeValid (char* s, char* locked) {
    int n = strlen (s);
    if (n % 2 != 0) return false;

    int open = 0, close = 0, unlocked1 = 0, unlocked2 = 0;
    for (int i = 0; i < n; i++) {
        if (locked [i] == '0') unlocked1++;
        else if (s [i] == '(') open++;
        else if (s [i] == ')') open--;
        if (open + unlocked1 < 0) return false;

        int j = n - i - 1;
        if (locked [j] == '0') unlocked2++;
        else if (s [j] == ')') close++;
        else if (s [j] == '(') close--;
        if (close + unlocked2 < 0) return false;
    }
    return true;
}