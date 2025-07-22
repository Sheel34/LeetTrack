unsigned char visited [1250];

bool test (int a) {
    return visited [a >> 3] & (1 << (a & 7)) ? true : false;
}

void set (int a) {
    visited [a>>3] |= 1 << (a & 7);
}

void reset (int a) {
    visited [a >> 3] &= ~(1 << (a & 7));
}

inline int max (int a, int b) {
    return a > b ? a : b;
}

int maximumUniqueSubarray (int* nums, int numsSize) {
    int ans = 0, sum = 0, i, j;
    memset (visited, 0, sizeof (visited));
    for (i = 0, j = 0; i < numsSize; i++) {
        while (test (nums [i] - 1)) {
            sum -= nums [j];
            reset (nums [j] - 1);
            j++;
        }
        sum += nums [i];
        set (nums [i] - 1);
        ans = max (ans, sum);
    }
    return ans;
}