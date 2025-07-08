int cmp(const void *a, const void *b) {
    int *eventA = *(int **)a;
    int *eventB = *(int **)b;
    return eventA[1] - eventB[1];
}

int maxValue(int** events, int eventsSize, int* eventsColSize, int k) {
    qsort(events, eventsSize, sizeof(int *), cmp);
    
    int *prev = (int *)malloc(eventsSize * sizeof(int));
    for (int i = 0; i < eventsSize; i++) {
        prev[i] = -1;
        int low = 0;
        int high = i - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (events[mid][1] < events[i][0]) {
                prev[i] = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
    }

    int *dp0 = (int *)calloc(eventsSize + 1, sizeof(int));
    int *dp1 = (int *)malloc((eventsSize + 1) * sizeof(int));

    for (int j = 1; j <= k; j++) {
        dp1[0] = 0;
        for (int i = 1; i <= eventsSize; i++) {
            int take = events[i-1][2];
            int p = prev[i-1];
            if (p != -1) {
                take += dp0[p + 1];
            }
            int not_take = dp1[i-1];
            dp1[i] = (take > not_take) ? take : not_take;
        }
        int *temp = dp0;
        dp0 = dp1;
        dp1 = temp;
    }

    int result = dp0[eventsSize];
    free(prev);
    free(dp0);
    free(dp1);
    return result;
}