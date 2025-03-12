int numberOfSubstrings (char* s) {
    int abc [3] = {-1, -1, -1};
    int count = 0, right = 0;
    while (s [right] != '\0') {
        abc [s [right] - 'a'] = right;
        int minIndex = INT_MAX;
        for (int i = 0; i < 3; i++) {
            if (abc [i] < minIndex) {
                minIndex = abc [i];
            }
        }
        count += (minIndex + 1);
        right++;
    }
    return count;
}