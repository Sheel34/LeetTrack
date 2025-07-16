int maximumLength (int* nums, int numsSize) {
    if (numsSize == 2) return 2;
        bool z = nums [0] & 1;
        int len [3] = {!z, z, 1};
        for (int i = 1; i < numsSize; i++) {
            bool x = nums [i] & 1;
            len [x & 1]++;
            if (x != z) {
                len [2]++;
                z = !z;
            }
        }
        return fmax (len [0], fmax (len [1], len [2]));
}