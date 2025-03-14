int maximumCandies (int* candies, int candiesSize, long long k) {
    int left = 1, right = 10000000;
        int result = 0;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            long childrenCount = 0;
            for (int i = 0; i < candiesSize; i++) {
                childrenCount += candies [i] / mid;
            }

            if (childrenCount >= k) {
                result = mid;
                left = mid + 1;
            } else
                right = mid - 1;
        }
        return result;
}