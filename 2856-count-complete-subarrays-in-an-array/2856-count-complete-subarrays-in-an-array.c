int countCompleteSubarrays (int* nums, int numsSize) {
    short count [2000] = {0};
    short diff = 0;
    for(int i = 0; i < numsSize; i++) {
        if (count [nums [i] - 1] == 0)
            diff++;
        count [nums [i] - 1]++;
    }
    memset (count, 0, 2000 * sizeof (short));
    int result = 0;
    short temp = 0, right = 0;
    for (short left = 0; left < numsSize; left++) {
        if (left > 0) {
            count [nums [left - 1] - 1]--;
            if (count [nums [left - 1] - 1] == 0)
                temp--;
        }
        while (right < numsSize && temp < diff) {
            if (count [nums [right] - 1] == 0)
                temp++;
            count [nums [right] - 1]++;
            right++;
        }
        if (temp == diff)
            result += numsSize - right + 1;
    }
    return result;
}