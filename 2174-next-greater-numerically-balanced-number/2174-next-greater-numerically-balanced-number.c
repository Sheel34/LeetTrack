bool isBeautiful (int count [10]) {
    for (int d = 1; d <= 7; d++) {
        if (count [d] != 0 && count [d] != d) return false;
    }
    return true;
}

void generate (long num, int count [10], int *res, int *resSize) {
    if (num > 0 && isBeautiful (count)) {
        res [(*resSize)++] = (int) num;
    }
    if (num > 1224444) return;
    for (int d = 1; d <= 7; d++) {
        if (count [d] < d) {
            count [d]++;
            generate (num * 10 + d, count, res, resSize);
            count [d]--;
        }
    }
}

int nextBeautifulNumber (int n) {
    int res [2000];
    int resSize = 0;
    int count [10] = {0};
    generate (0, count, res, &resSize);
    int ans = -1;
    for (int i = 0; i < resSize; i++) {
        if (res [i] > n && (ans == -1 || res [i] < ans)) ans = res [i];
    }
    return ans;
}