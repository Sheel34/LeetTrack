#pragma GCC optimize("O3", "unroll-loops")
static int seg[262144];
static void build (int* A, int idx, int l, int r) {
    if (l == r) seg [idx] = A [l];
    else{
        const int m = (l + r) / 2;
        build (A, 2 * idx, l, m);
        build (A, 2 * idx + 1, m + 1, r);
        seg [idx] = fmax (seg [2 * idx], seg [2 * idx + 1]);
    }
}
static int search (int idx, int l, int r, int k) {
    if (seg [idx] < k) return -1;
    if (l==r) {
        seg [idx] = -1;
        return l;
    }
    const int m = (l + r) / 2;
    int pos;
    if (seg [2 * idx] >= k) pos = search (2 * idx, l, m, k);
    else pos = search (2 * idx + 1, m + 1, r, k);
    seg [idx] = fmax (seg [2 * idx], seg [2 * idx + 1]);
    return pos;
}

int numOfUnplacedFruits (int* fruits, int fruitsSize, int* baskets, int basketsSize) {
    int ans = 0;
    memset (seg, 0, fmin (4 * 262144, 4 * fruitsSize * sizeof (int)));
    build (baskets, 1, 0, fruitsSize - 1);
    for (int i = 0; i < fruitsSize; i++){
        if (search (1, 0, fruitsSize - 1, fruits [i]) == -1) ans++;
    }
    return ans;
}