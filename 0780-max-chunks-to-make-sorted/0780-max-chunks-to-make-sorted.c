int maxx (int x, int y) { return x > y ? x : y; }

int maxChunksToSorted (int* arr, int arrSize) {
    if (arr == NULL || arrSize == 0)
            return 0;

        int count = 0, max = 0;
        for (int i = 0; i < arrSize; i++) {
            max = maxx (max, arr [i]);
            if (max == i)
                count++;
        }
        return count;
}