bool check (int n, int freq []) {
    int count [10] = {};
    while (n > 0) {
        count [n % 10]++;
        n /= 10;
    }
    for (int i = 0; i < 10; i++)
        if (freq [i] != count [i])
            return false;
    return true;
}

bool reorderedPowerOf2 (int n) {
    int freq [10] = {};
    while (n > 0) {
        freq [n % 10]++;
        n /= 10;
    }
    for (int i = 0; i < 31; i++)
        if (check (1 << i, freq))
            return true;
    return false;
}