#define MAX_QUEUE 1000000

typedef struct {
    char str [8];  
    int len;
} Node;

char best [8]; 

int isSubsequence (const char* s, const char* t) {
    int i = 0, j = 0;
    int len_s = strlen (s), len_t = strlen (t);
    while (i < len_s && j < len_t) {
        if (s [i] == t [j]) j++;
        i++;
    }
    return j == len_t;
}

int isKRepeatedSubsequence (const char* s, const char* seq, int k) {
    int len = strlen (seq);
    int total_len = len * k;
    if (total_len > strlen (s)) return 0; 

    char* repeated = (char*) malloc (total_len + 1);
    if (!repeated) return 0;

    for (int i = 0; i < k; ++i)
        strncpy (repeated + i * len, seq, len);
    repeated[total_len] = '\0';

    int res = isSubsequence (s, repeated);
    free (repeated);
    return res;
}

char* longestSubsequenceRepeatedK (char* s, int k) {
    int freq [26] = {0};
    int len_s = strlen(s);

    for (int i = 0; i < len_s; ++i) 
        freq [s [i] - 'a']++;

    char chars [27];
    int idx = 0;
    for (int i = 25; i >= 0; --i) {
        if (freq [i] >= k)
            chars [idx++] = 'a' + i;
    }
    chars [idx] = '\0';

    Node queue [MAX_QUEUE];
    int front = 0, back = 0;

    queue [back++] = (Node) {"", 0};
    best [0] = '\0';

    int max_len = 0; 

    while (front < back) {
        Node node = queue[front++];
        char* cur = node.str;

        if (node.len < max_len) continue;

        if (isKRepeatedSubsequence(s, cur, k)) {
            if (node.len > max_len || (node.len == max_len && strcmp(cur, best) > 0)) {
                strcpy(best, cur);
                max_len = node.len;
            }
        } else continue; 

        if (node.len == 7 || node.len >= len_s / k) continue;

        for (int i = 0; i < idx; ++i) {
            if (back >= MAX_QUEUE) break; 

            Node next;
            strcpy (next.str, cur);
            next.str [node.len] = chars [i];
            next.str [node.len + 1] = '\0';
            next.len = node.len + 1;

            queue [back++] = next;
        }
    }
    return strdup (best);
}