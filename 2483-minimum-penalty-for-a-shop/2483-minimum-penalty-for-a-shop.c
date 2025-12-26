int bestClosingTime (char* customers) {
    int bestTime = 0, min = 0, pre = 0;
    for (int i = 0; i < strlen (customers); i++) {
        pre += (customers [i] == 'Y') ? -1 : 1;
        if (pre < min) {
            bestTime = i + 1;
            min = pre;
        }
    }
    return bestTime;
}