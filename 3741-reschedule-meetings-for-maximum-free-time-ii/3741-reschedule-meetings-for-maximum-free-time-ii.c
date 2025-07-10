int max (int a, int b) {
    return (a >= b) ? a : b;
}

int maxFreeTime (int eventTime, int* startTime, int startTimeSize, int* endTime, int endTimeSize) {
    int gaps [startTimeSize + 1];

    gaps [0] = startTime [0] - 0;
    for (int i = 1; i < startTimeSize; i++)
        gaps [i] = startTime [i] - endTime [i - 1];
    gaps [startTimeSize] = eventTime - endTime [startTimeSize - 1];

    int prefix_arr [startTimeSize + 1];
    prefix_arr [0] = gaps [0];
    for (int i = 1; i <= startTimeSize; i++)
        prefix_arr [i] = max (prefix_arr [i - 1], gaps [i]);

    int suffix_arr [startTimeSize + 1];
    suffix_arr [startTimeSize] = gaps [startTimeSize];
    for (int i = startTimeSize - 1; i >= 0; i--)
        suffix_arr [i] = max (suffix_arr [i + 1], gaps [i]);

    int max_gap = 0;
    for(int i = 0; i < startTimeSize; i++) {
        int before = (i - 1 >= 0) ? prefix_arr [i - 1] : 0;
        int after = (i + 2 <= startTimeSize) ? suffix_arr [i + 2] : 0;

        if ((endTime [i] - startTime [i]) <= max (before, after)) {
            int temp_max = (endTime [i] - startTime [i]) + gaps [i] + gaps [i + 1];
            max_gap = max (max_gap, temp_max);
        }
        else{
            max_gap = max (max_gap, gaps [i] + gaps [i + 1]);
        }
    }
    return max_gap;
}