long long minSum (int* nums1, int n1, int* nums2, int n2) {
    long long sum1 = 0, sum2 = 0;
    int zero1 = 0, zero2 = 0;
    for (int i = 0; i < n1; i++) {
        const int x = nums1 [i];
        sum1 += x;
        zero1 += x == 0;
    }
    for(int i = 0; i < n2; i++) {
        const int x = nums2 [i];
        sum2 += x;
        zero2 += x == 0;
    }
    if ((zero1 == 0 && sum1 < sum2 + zero2) || (zero2 ==0 && sum2 < sum1 + zero1))
        return -1;
    return sum1 + zero1 > sum2 + zero2 ? sum1 + zero1 : sum2 + zero2;
}