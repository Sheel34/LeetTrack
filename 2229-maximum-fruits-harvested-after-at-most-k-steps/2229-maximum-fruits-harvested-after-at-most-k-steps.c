int maxTotalFruits (int** fruits, int fruitsSize, int* fruitsColSize, int startPos, int k) {
    int min (int a, int b) {
    return (a > b) ? b : a;
    }
    int max (int a, int b) {
        return (a > b) ? a : b;
    }
    int minpos (int left, int right, int start) {
        return min (abs (start - left) + (right - left), abs (right - start) + (right - left));
    }
    int left = 0, res = 0, cur = 0;
    for (int right = 0; right < fruitsSize; right++) {
        cur += fruits [right] [1];
        while (left <= right && minpos (fruits [left] [0], fruits [right] [0], startPos) > k) {
            cur -= fruits [left] [1];
            left++;
        }
        res = max (res, cur);
    }
    return res;
}