long long min (long long a, long long b) {
    return (a < b) ? a : b;
}

void minHeapify (int* arr, int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr [left] < arr [smallest])
        smallest = left;
    if (right < n && arr [right] < arr [smallest])
        smallest = right;
    if (smallest != i) {
        int temp = arr [i];
        arr [i] = arr [smallest];
        arr [smallest] = temp;
        minHeapify(arr, n, smallest);
    }
}

void buildMinHeap (int* arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        minHeapify (arr, n, i);
    }
}

void maxHeapify (int* arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr [left] > arr [largest])
        largest = left;
    if (right < n && arr [right] > arr [largest])
        largest = right;
    if (largest != i) {
        int temp = arr [i];
        arr [i] = arr [largest];
        arr [largest] = temp;
        maxHeapify (arr, n, largest);
    }
}
void buildMaxHeap (int* arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        maxHeapify (arr, n, i);
    }
}


long long minimumDifference (int* nums, int numsSize) {
    long long leftSum [numsSize];
    long long rightSum [numsSize];
    int n = numsSize / 3;
    int leftHeap [n];
    int rightHeap [n];
    for (int i = 0; i < numsSize; i++) {
    leftSum [i] = 0;
    rightSum [i] = 0;
    }
    for (int i = 0; i < n; i++){
    leftHeap [i] = 0;
    rightHeap [i] = 0;
    }
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        leftHeap [i] = nums [i];
        sum += nums [i];
        leftSum [i] = sum;
    }
    buildMaxHeap (leftHeap, n);
    for (int i = n; i < 2 * n; i++) {
        if (nums [i] < leftHeap [0]) {
            sum += nums [i];
            sum -= leftHeap [0];
            leftHeap [0] = nums [i];
            maxHeapify (leftHeap, n, 0);
        }
        leftSum [i] = sum;
    }
    sum = 0;
    int index = 0;
    for (int i = numsSize - 1; i > 2 * n; i--) {
        rightHeap [index] = nums [i];
        sum += nums [i];
        rightSum [i] = sum; index++;
    }
    buildMinHeap (rightHeap, n);
    for (int i = 2 * n; i >= n; i--) {
        if (nums [i] > rightHeap [0]) {
            sum += nums [i];
            sum -= rightHeap [0];
            rightHeap [0] = nums [i];
            minHeapify (rightHeap, n, 0);
        }
        rightSum [i]=sum;
    }
    long long result = LLONG_MAX;
    for (int i = n - 1; i <= 2 * n - 1; i++) {
        long long diff = leftSum [i] - rightSum [i + 1];
        result = min (result, diff);
    }
    return result;
}