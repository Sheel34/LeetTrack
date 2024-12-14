long long continuousSubarrays (int* nums, int numsSize){

    long long count = 0;
    int left = 0, right = 0;

    int maxDeque [numsSize], minDeque [numsSize];
    int maxStart = 0, maxEnd = -1, minStart = 0, minEnd = -1;

    while (right < numsSize) {
        int current = nums [right];

        while (maxEnd >= maxStart && maxDeque [maxEnd] < current) {
            maxEnd--;
        }
        maxDeque [++maxEnd] = current;

        while (minEnd >= minStart && minDeque [minEnd] > current) {
            minEnd--;
        }
        minDeque [++minEnd] = current;

        while (maxDeque [maxStart] - minDeque [minStart] > 2) {
            if (nums [left] == maxDeque [maxStart]) {
                maxStart++;
            }
            if (nums [left] == minDeque [minStart]) {
                minStart++;
            }
            left++;
        }

        count += (right - left + 1);
        right++;
    }

    return count;
}