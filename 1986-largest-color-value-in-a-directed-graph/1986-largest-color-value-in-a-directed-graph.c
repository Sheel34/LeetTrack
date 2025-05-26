typedef struct node {
    char color;
    int *nexts;
    int len;
    int cap;
    int maxCnts[26];
} node;

void addNext(node *f, int c) {
    f->nexts[f->len] = c;
    if (++f->len == f->cap) {
        f->cap *= 2;
        f->nexts = realloc(f->nexts, f->cap * sizeof(int));
    }
}

void dfs(node *nodeList, int f, bool *accessed, bool *searched, bool *flgLoop) {
    accessed[f] = true;
    nodeList[f].maxCnts[nodeList[f].color] = 1;
    for (int i = 0; i < nodeList[f].len; i++) {
        int c = nodeList[f].nexts[i];
        if (accessed[c] == false) {
        dfs(nodeList, c, accessed, searched, flgLoop);
        } else {
        if (searched[c] == false) {
            *flgLoop = true;
            return;
        }
        }
        for (int j = 0; j < 26; j++) {
        if (j != nodeList[f].color) {
            if (nodeList[c].maxCnts[j] > nodeList[f].maxCnts[j])
            nodeList[f].maxCnts[j] = nodeList[c].maxCnts[j];
        } else {
            if (nodeList[c].maxCnts[j] + 1 > nodeList[f].maxCnts[j])
            nodeList[f].maxCnts[j] = nodeList[c].maxCnts[j] + 1;
        }
        }
    }
    searched[f] = true;
}


int largestPathValue(char * colors, int** edges, int edgesSize, int* edgesColSize){
    int n = strlen(colors);
    node *nodeList = calloc(n, sizeof(node));
    for (int i = 0; i < n; i++)
        nodeList[i] = (node){colors[i] - 'a', malloc(4 * sizeof(int)), 0, 4};
    for (int i = 0; i < edgesSize; i++)
        addNext(&nodeList[edges[i][0]], edges[i][1]);

    int rs = 0;
    bool searched[n], accessed[n];
    memset(searched, 0, sizeof(searched));
    memset(accessed, 0, sizeof(searched));
    bool flgLoop = false;
    for (int i = 0; i < n; i++) {
        if (searched[i] == false)
        dfs(nodeList, i, accessed, searched, &flgLoop);
        if (flgLoop) {
        rs = -1;
        goto RETURN;
        }
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < 26; j++)
        if (nodeList[i].maxCnts[j] > rs)
            rs = nodeList[i].maxCnts[j];

    RETURN:
    for (int i = 0; i < n; i++)
        free(nodeList[i].nexts);
    free(nodeList);
    return rs;
}