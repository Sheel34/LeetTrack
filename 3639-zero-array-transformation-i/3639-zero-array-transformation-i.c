#pragma GCC optimize("O3", "unroll-loops")

bool isZeroArray(int* nums, int n, int** queries, int m, int* queriesColSize) {
    *queriesColSize = 2;
    int freq[n+1];
    memset(freq, 0, sizeof(freq));
    for (int i=0; i<m; i++) {
        const int s=queries[i][0], e=queries[i][1];
        freq[s]++;
        freq[e+1]--;
    }
    int op=0;
    for (int i=0;i<n; i++) {
        op+=freq[i];
        if (nums[i]>op)
            return 0;
    }
    return 1;
}