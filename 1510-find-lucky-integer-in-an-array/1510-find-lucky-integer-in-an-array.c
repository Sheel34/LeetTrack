int findLucky (int* arr, int arrSize) {
    int count = 0, max = INT_MIN;
    for (int i = 0; i < arrSize; i++) {
        count = 0;
        int num = arr [i];
        for (int j = 0; j < arrSize; j++) {
            if (num == arr [j])
                count++;
        }
        if (num == count)
            max = fmax (num, max);
    }
    if (max == INT_MIN)
        return -1;
    else
        return max;
}