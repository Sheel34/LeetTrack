enum {VAL,NEXT};
int maxDiameter (int **edges, int edgesSize);


int minimumDiameterAfterMerge (int** edges1, int edges1Size, int* edges1ColSize, int** edges2, int edges2Size, int* edges2ColSize) {
    int diam1 = maxDiameter (edges1, edges1Size);
    int diam2 = maxDiameter (edges2, edges2Size);
    int diam3 = (diam1 >> 1) + (diam1 & 1);
    diam3 += (diam2 >> 1) + (diam2 & 1) + 1;
    if (diam1 < diam2) diam1 = diam2;
    if (diam1 < diam3) diam1 = diam3;
    return diam1;
}

int maxDiameter (int **edges, int edgesSize) {
    int i, n = edgesSize + 1, queue [n + 1], head = 0, tail = 0;
    int ht [n], nodes [(edgesSize << 1) + 1][2], node, nodePtr = 0;
    int count, last, curr, nxt, diam = 0;
    bool visited [n];
    memset (visited, 0, sizeof (visited));
    memset (ht, -1, sizeof (ht));
    for (i = 0; i < edgesSize; ++i) {
        node = nodePtr++;
        nodes [node] [VAL] = edges [i] [0];
        nodes [node] [NEXT] = ht [edges [i] [1]];
        ht [edges [i] [1]] = node;
        node = nodePtr++;
        nodes [node] [VAL] = edges [i] [1];
        nodes [node] [NEXT] = ht [edges [i] [0]];
        ht [edges [i] [0]] = node;
    }
    visited [0] = true;
    queue [tail++] = 0;
    while (head < tail) {
        count = tail - head;
        while (count--) {
            curr = queue [head++];
            node = ht [curr];
            while (node >= 0) {
                nxt = nodes [node] [VAL];
                node = nodes [node] [NEXT];
                if (visited [nxt]) continue;
                visited [nxt] = true;
                queue [tail++] = nxt;
            }
        }
    }
    memset (visited, 0, sizeof (visited));
    head = 0; tail = 1; queue [0] = curr;
    while (head < tail) {
        count = tail - head;
        while (count--) {
            curr = queue [head++];
            node = ht [curr];
            while (node >= 0) {
                nxt = nodes [node] [VAL];
                node = nodes [node] [NEXT];
                if (visited [nxt]) continue;
                visited [nxt] = true;
                queue [tail++] = nxt;
            }
        }
        if (head < tail) ++diam;
    }
    return diam;
}