#define MAXN 1005
#define INF 1000000000

int nums[MAXN];
int child_xor[MAXN];
int childs[MAXN][MAXN];
int visited[MAXN];
int adj[MAXN][MAXN], adjSize[MAXN];
int pc[MAXN * 2][2], pcSize = 0;
int par[MAXN], parSize = 0;

int max3(int a, int b, int c) {
    int max = a > b ? a : b;
    return max > c ? max : c;
}

int min3(int a, int b, int c) {
    int min = a < b ? a : b;
    return min < c ? min : c;
}

int dfs(int node) {
    visited[node] = 1;
    int ans = nums[node];

    for (int i = 0; i < parSize; ++i)
        childs[par[i]][node] = 1;

    par[parSize++] = node;

    for (int i = 0; i < adjSize[node]; ++i) {
        int child = adj[node][i];
        if (!visited[child]) {
            pc[pcSize][0] = node;
            pc[pcSize][1] = child;
            pcSize++;
            ans ^= dfs(child);
        }
    }

    parSize--;
    child_xor[node] = ans;
    return ans;
}

int minimumScore(int* numsInput, int numsSize, int** edges, int edgesSize, int* edgesColSize) {
    for (int i = 0; i < numsSize; ++i)
        nums[i] = numsInput[i];

    pcSize = 0;
    parSize = 0;
    memset(adjSize, 0, sizeof(adjSize));
    memset(visited, 0, sizeof(visited));
    memset(childs, 0, sizeof(childs));
    memset(child_xor, 0, sizeof(child_xor));

    for (int i = 0; i < edgesSize; ++i) {
        int u = edges[i][0];
        int v = edges[i][1];
        adj[u][adjSize[u]++] = v;
        adj[v][adjSize[v]++] = u;
    }

    dfs(0);

    int ans = INF;

    for (int i = 0; i < pcSize; ++i) {
        for (int j = i + 1; j < pcSize; ++j) {
            int a = pc[i][1];
            int b = pc[j][1];

            int xa = child_xor[a];
            int xb = child_xor[b];
            int xc = child_xor[0];

            if (childs[a][b]) {
                xc ^= xa;
                xa ^= xb;
            } else if (childs[b][a]) {
                xc ^= xb;
                xb ^= xa;
            } else {
                xc ^= xa;
                xc ^= xb;
            }

            int mx = max3(xa, xb, xc);
            int mn = min3(xa, xb, xc);
            if (ans > mx - mn)
                ans = mx - mn;
        }
    }

    return ans;
}