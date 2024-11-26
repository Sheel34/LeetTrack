int findChampion (int n, int** edges, int edgesSize, int* edgesColSize) {
    int arr [n] = {};
    for (int i = 0; i < edgesSize; i++) {
        arr [edges [i] [1]]++;
    }
    int res = -1, count = 0;
    for (int i = 0; i < n; i++) {
        if (arr [i] == 0) {
            res = i;
            count++;
        }
        if (count > 1) return -1;
    }
    return res;
}