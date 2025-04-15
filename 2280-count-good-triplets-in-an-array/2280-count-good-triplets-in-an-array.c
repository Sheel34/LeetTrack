#define MAXN 100010

int tree [MAXN];

void update (int index,int val,int n){
    index++;
    while(index <= n + 2) {
        tree [index] += val;
        index += index & (-index);
    }
}

int query (int index) {
    index++;
    int res = 0;
    while (index > 0) {
        res += tree [index];
        index -= index & (-index);
    }
    return res;
}

long long goodTriplets (int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int n = nums1Size;
    int pos2 [MAXN];
    for (int i = 0; i < n; i++)
        pos2 [nums2 [i]] = i;
    int arr [MAXN];
    for (int i = 0; i < n; i++)
        arr [i] = pos2 [nums1 [i]];
    int left_count [MAXN] = {0};
    memset (tree, 0, sizeof (tree));
    for (int i = 0; i < n; i++) {
        left_count [i] = query (arr [i] - 1);
        update (arr [i], 1, n);
    }
    memset (tree, 0, sizeof (tree));
    long long ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        int right_count = query (n - 1) - query (arr [i]);
        ans += (long long) left_count [i] * right_count;
        update (arr [i], 1, n);
    }
    return ans;
}