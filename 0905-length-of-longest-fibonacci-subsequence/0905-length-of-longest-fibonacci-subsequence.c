int lenLongestFibSubseq (int* arr, int arrSize) {
    int dp [arrSize] [arrSize];
    memset (dp, 0, sizeof (dp));
    int maxLen = 0;
    for (int i = 2; i < arrSize; i++) {
        int start = 0, end = i - 1;
        while (start < end) {
            int pairSum = arr [start] + arr [end];
            if (pairSum > arr [i])
                end--;
            else if (pairSum < arr [i])
                start++;
            else {
                dp [end] [i] = dp [start] [end] + 1;
                maxLen = fmax (dp [end] [i], maxLen);
                end--;
                start++;
            }
        }
    }
    return maxLen == 0 ? 0 : maxLen + 2;
}