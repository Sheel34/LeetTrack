int maxFreeTime (int eventTime, int k, int* startTime, int startTimeSize, int* endTime, int endTimeSize) {
    int* gaps = (int*)malloc((startTimeSize + 1) * sizeof(int));
    gaps[0] = startTime[0];
    for (int i = 1; i < startTimeSize; i++) {
        gaps[i] = startTime[i] - endTime[i - 1];
    }
    gaps[startTimeSize] = eventTime - endTime[startTimeSize - 1];
    int windowSum = 0;
    for (int i = 0; i < k + 1; i++) {
        windowSum += gaps[i];
    }
    int maxFree = windowSum;
    for (int i = k + 1; i < startTimeSize + 1; i++) {
        windowSum += gaps[i] - gaps[i - (k + 1)];
        maxFree = windowSum > maxFree ? windowSum : maxFree;
    }
    return maxFree;
}