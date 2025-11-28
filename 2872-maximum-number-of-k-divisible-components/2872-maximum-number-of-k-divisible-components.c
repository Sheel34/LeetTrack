int dfs (int** adj, int* adjSize, int* values, int* res, int node, int parent, int k) {
    long long sum = values [node];
    for (int i = 0; i < adjSize [node]; i++) {
        int next = adj [node] [i];
        if (next != parent) sum += dfs (adj, adjSize, values, res, next, node, k);
    }
    if (sum % k == 0) (*res)++;
    return sum % k;
}

int maxKDivisibleComponents (int n, int** edges, int edgesSize, int* edgesColSize, int* values, int valuesSize, int k) {
    int* adjSize = calloc (n, sizeof (int));
    for (int i = 0; i < edgesSize; i++) {
        adjSize [edges [i] [0]]++;
        adjSize [edges [i] [1]]++;
    }
    int ** adj = malloc (n * sizeof (int*));
    for (int i = 0; i < n; i++) adj [i] = malloc (adjSize [i] * sizeof (int));
    int* count = calloc (n, sizeof (int));
    for (int i = 0; i < edgesSize; i++) {
        int a = edges [i] [0], b = edges [i] [1];
        adj [a] [count [a]++] = b;
        adj [b] [count [b]++] = a;
    }
    int res = 0;
    dfs (adj, adjSize, values, &res, 0, -1, k);
    return res;
}