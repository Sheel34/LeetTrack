typedef struct {
    int start;
    int end;
    int value;
} Event;

static int compareEvents(const void* a, const void* b) {
    Event* e1 = (Event*)a;
    Event* e2 = (Event*)b;
    if (e1->end == e2->end) {
        return (e1->start - e2->start);
    }
    return (e1->end < e2->end) ? -1 : 1;
}

int binarySearch(Event* events, int size, int startTime) {
    int left = 0, right = size - 1;
    int ans = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (events[mid].end < startTime) {
            ans = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return ans;
}

int maxTwoEvents(int** events, int eventsSize, int* eventsColSize) {
    
    Event* arr = (Event*)malloc(sizeof(Event)*eventsSize);
    for (int i = 0; i < eventsSize; i++) {
        arr[i].start = events[i][0];
        arr[i].end = events[i][1];
        arr[i].value = events[i][2];
    }

    qsort(arr, eventsSize, sizeof(Event), compareEvents);

    int* prefixMax = (int*)malloc(sizeof(int)*eventsSize);
    
    prefixMax[0] = arr[0].value;
    for (int i = 1; i < eventsSize; i++) {
        prefixMax[i] = (prefixMax[i-1] > arr[i].value) ? prefixMax[i-1] : arr[i].value;
    }

    int result = 0;
    for (int i = 0; i < eventsSize; i++) {
        if (arr[i].value > result) {
            result = arr[i].value; 
        }
    }

    for (int i = 0; i < eventsSize; i++) {
        int idx = binarySearch(arr, eventsSize, arr[i].start);
        int bestBefore = (idx == -1) ? 0 : prefixMax[idx];
        int candidate = arr[i].value + bestBefore;
        if (candidate > result) {
            result = candidate;
        }
    }

    free(prefixMax);
    free(arr);
    return result;
}