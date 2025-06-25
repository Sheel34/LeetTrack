long long kthSmallestProduct (int* nums1, int nums1Size, int* nums2, int nums2Size, long long k) {
    int len1 = nums1Size, len2 = nums2Size;
    int neg1 = 0, neg2 = 0;
    
    while (neg1 < len1 && nums1 [neg1] < 0) neg1++;
    while (neg2 < len2 && nums2 [neg2] < 0) neg2++;

    long long lo = -1e10, hi = 1e10;

    while (lo <= hi) {
        long long mid = (lo + hi) / 2;
        long long total = 0;
        {
            int i = 0, j = neg2 - 1;
            while (i < neg1 && j >= 0) {
                if ((long long) nums1 [i] * nums2 [j] > mid)
                    i++;
                else {
                    total += neg1 - i;
                    j--;
                }
            }
        }

        {
            int i = neg1, j = len2 - 1;
            while (i < len1 && j >= neg2) {
                if ((long long)nums1[i] * nums2[j] > mid)
                    j--;
                else {
                    total += j - neg2 + 1;
                    i++;
                }
            }
        }

        {
            int i = 0, j = neg2;
            while (i < neg1 && j < len2) {
                if ((long long)nums1[i] * nums2[j] > mid)
                    j++;
                else {
                    total += len2 - j;
                    i++;
                }
            }
        }

        {
            int i = neg1, j = 0;
            while (i < len1 && j < neg2) {
                if ((long long) nums1 [i] * nums2 [j] > mid)
                    i++;
                else {
                    total += len1 - i;
                    j++;
                }
            }
        }

        if (total < k)
            lo = mid + 1;
        else
            hi = mid - 1;
    }
    return lo;
}