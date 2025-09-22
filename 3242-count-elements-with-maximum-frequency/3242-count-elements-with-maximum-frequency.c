int maxFrequencyElements (int* nums, int numsSize) {
    uint8_t freq [101] = {0};
        uint8_t max = 0, res = 0;
        for (int i = 0; i < numsSize; i++) {
            uint8_t f = ++freq [nums [i]];
            if (f > max) {
                max = f;
                res = f;
            } else if (f == max)
                res += f;
        }
        return res;
}