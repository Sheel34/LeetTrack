/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

typedef struct { uint64_t pat; int idx; } Pattern;

char** getWordsInLongestSubsequence (char** words, int wordsSize, int* groups, int groupsSize, int* returnSize) {
    int n = wordsSize;
    if (n == 0) { *returnSize = 0; return NULL; }
    uint64_t* codes = malloc(n * sizeof(uint64_t));
    for (int i = 0; i < n; ++i) {
        uint64_t code = 0;
        for (int j = 0; words[i][j]; ++j) {
            code |= (uint64_t)(words[i][j] - 'a') << (5 * j);
        }
        codes[i] = code;
    }
    int* dp = malloc(n * sizeof(int));
    int* prev = malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) { dp[i] = 1; prev[i] = -1; }
    int max_len = 1, max_idx = 0;
    Pattern* patterns[11][11] = {{0}};
    int sizes[11][11] = {0}, caps[11][11] = {0};
    for (int i = 0; i < n; ++i) {
        int L = strlen(words[i]), g = groups[i];
        uint64_t code_i = codes[i];
        for (int j = 0; j < L; ++j) {
            if (caps[L][j] == 0) {
                caps[L][j] = 16;
                patterns[L][j] = malloc(caps[L][j] * sizeof(Pattern));
                sizes[L][j] = 0;
            }
        }
        int best = 1, bp = -1;
        for (int j = 0; j < L; ++j) {
            uint64_t mask = ~((uint64_t)31 << (5 * j));
            uint64_t pat = code_i & mask;
            Pattern* arr = patterns[L][j];
            int sz = sizes[L][j];
            for (int k = 0; k < sz; ++k) {
                if (arr[k].pat == pat) {
                    int idx = arr[k].idx;
                    if (groups[idx] != g && dp[idx] + 1 > best) {
                        best = dp[idx] + 1;
                        bp = idx;
                    }
                }
            }
        }
        dp[i] = best; prev[i] = bp;
        if (best > max_len) { max_len = best; max_idx = i; }
        for (int j = 0; j < L; ++j) {
            uint64_t mask = ~((uint64_t)31 << (5 * j));
            uint64_t pat = code_i & mask;
            if (sizes[L][j] == caps[L][j]) {
                caps[L][j] *= 2;
                patterns[L][j] = realloc(patterns[L][j], caps[L][j] * sizeof(Pattern));
            }
            patterns [L][j][sizes[L][j]].pat = pat;
            patterns [L][j][sizes[L][j]].idx = i;
            sizes [L] [j]++;
        }
    }
    char** temp = malloc (max_len * sizeof (char*));
    int cnt = 0;
    for (int cur = max_idx; cur != -1; cur = prev [cur]) {
        temp [cnt++] = strdup (words [cur]);
    }
    char** res = malloc (cnt * sizeof (char*));
    for (int i = 0; i < cnt; ++i) {
        res [i] = temp [cnt - 1 - i];
    }
    *returnSize = cnt;
    return res;
}