void heapify (int* gifts, int giftsSize, int i) {

    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < giftsSize && gifts [left] > gifts [largest]) {
        largest = left;
    }

    if (right < giftsSize && gifts [right] > gifts [largest]) {
        largest = right;
    }

    if (largest != i) {
        int temp = gifts [i];
        gifts [i] = gifts [largest];
        gifts [largest] = temp;

        heapify (gifts, giftsSize, largest);
    }
}

long long pickGifts (int* gifts, int giftsSize, int k) {

    long long total = 0;
    for (int i = 0; i < giftsSize; i++) {
        total += gifts [i];
    }

    for (int i = giftsSize / 2 - 1; i >= 0; i--) {
        heapify (gifts, giftsSize, i);
    }

    for (int i = 0; i < k; i++) {

        int largest = gifts [0];

        int new_value = (int) sqrt (largest);

        total -= (largest - new_value);

        gifts [0] = new_value;

        heapify (gifts, giftsSize, 0);
    }

    return total;
}