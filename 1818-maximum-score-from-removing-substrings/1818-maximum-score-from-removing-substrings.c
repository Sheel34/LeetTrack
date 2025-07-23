int maximumGain(char* s, int x, int y) {
    int n = strlen(s), profit = 0;
    char stack1[n], stack2[n];
    int top1 = -1, top2 = -1;

    if (x > y) {
        for (int i = 0; i < n; i++) {
            stack1[++top1] = s[i];
            if (top1 >= 1 && stack1[top1 - 1] == 'a' && stack1[top1] == 'b') {
                top1 -= 2;
                profit += x;
            }
        }
    } else {
        for (int i = 0; i < n; i++) {
            stack1[++top1] = s[i];
            if (top1 >= 1 && stack1[top1 - 1] == 'b' && stack1[top1] == 'a') {
                top1 -= 2;
                profit += y;
            }
        }
    }

    for (int i = 0; i <= top1; i++) {
        stack2[++top2] = stack1[i];
        if (top2 >= 1) {
            if (stack2[top2 - 1] == 'a' && stack2[top2] == 'b') {
                top2 -= 2;
                profit += x;
            } else if (stack2[top2 - 1] == 'b' && stack2[top2] == 'a') {
                top2 -= 2;
                profit += y;
            }
        }
    }

    return profit;
}