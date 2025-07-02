#define MOD 1000000007

int countWays (int* arr, int n, int k) {
    int dp [k];
    int ndp [k];
    memset (dp, 0, sizeof (dp));
    dp [0] = 1;

    for (int i = 0; i < n; i++) {
        memset (ndp, 0, sizeof (ndp));
        int sum = 0;
        for (int j = 0; j < k; j++) {
            if (j == 0) sum = dp [0];
            else sum = (sum + dp [j]) % MOD;
            if (j > arr [i]) sum = (sum - dp [j - arr [i] - 1] + MOD) % MOD;
            ndp [j] = sum;
        }
        memcpy (dp, ndp, sizeof (dp));
    }
    int result = 0;
    for (int j = 0; j < k; j++) { result = (result + dp [j]) % MOD; }
    return result;
}

int countCombinationsAtLeastK (int* arr, int n, int k) {
    long long total = 1;
    for (int i = 0; i < n; i++) {
        total = (total * (arr [i] + 1)) % MOD;
    }
    int lessThanK = countWays (arr, n, k);
    return (total - lessThanK + MOD) % MOD;
}

int possibleStringCount (char* word, int k) {
    int len = strlen (word);
    
    int arr [len];
    int index = 0;

    int i = 0;
    while (i < len) {
        int count = 0;
        while (word [i + count] == word [i]) {
            count++;
        }
        arr [index++] = count - 1;
        i += count;
    }
    for(int i=0; i<index; i++) {
        printf("%d ", arr[i]);
    }
    if (index >= k) {
        long long total = 1;
        for (int i = 0; i < index; i++) 
            total = (total * (arr [i] + 1)) % MOD;
        return (int) total;
    }
    return countCombinationsAtLeastK (arr, index, k-index); 
}