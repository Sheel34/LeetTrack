#define MOD 1000000007

int traverse (int level, int index, int freq [] [26], char* target, int** memo, int n, int m);


int numWays (char** words, int wordsSize, char* target) {
    int n = strlen (words [0]);
    int m = strlen (target);
    int freq [n] [26];
    memset(freq, 0, sizeof (freq));

    for (int i = 0; i < wordsSize; i++) {
        for (int j = 0; j < n; j++) {
            freq [j] [words [i] [j] - 'a']++;
        }
    }

    int** memo = (int**) malloc ((n + 1) * sizeof (int*));
    for (int i = 0; i <= n; i++) {
        memo [i] = (int*) malloc ((m + 1) * sizeof (int));
        for (int j = 0; j <= m; j++) {
            memo [i] [j] = -1;
        }
    }

    int result = traverse (0, 0, freq, target, memo, n, m);

    for (int i = 0; i <= n; i++) {
        free (memo [i]);
    }
    free (memo);

    return result;
}

int traverse (int level, int index, int freq [] [26], char* target, int** memo, int n, int m) {
    if (index == m) return 1;
    if (level == n) return 0;
    if (memo [level] [index] != -1) return memo [level] [index];
    
    int ways = traverse (level + 1, index, freq, target, memo, n, m);
    
    if (freq [level] [target [index] - 'a'] > 0) {
        ways = (ways + (long long)freq [level] [target [index] - 'a'] * traverse (level + 1, index + 1, freq, target, memo, n, m)) % MOD;
    }
    
    return memo [level] [index] = ways;
}