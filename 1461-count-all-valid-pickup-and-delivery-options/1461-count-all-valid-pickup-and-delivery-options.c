int countOrders (int n) {
    int mod = (int) 1e9 + 7;
    long long count = 1;
    for (int i = 2; i <= n; i++)
        count = (count * (2 * i - 1) * i) % mod;
    return (int) count % mod;
}