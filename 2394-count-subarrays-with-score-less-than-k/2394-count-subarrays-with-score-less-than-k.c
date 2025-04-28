long long countSubarrays (int* nums, int numsSize, long long k) {
    long long count = 0, sum = 0;
    int left = 0;
    for (int right = 0; right < numsSize; right++) {
        sum += nums [right];
        while (sum * (right - left + 1) >= k)
            sum -= nums [left++];
        count += (right - left + 1);
    }
    return count;
}