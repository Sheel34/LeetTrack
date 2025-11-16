#pragma GCC optimize("O3, unroll-loops")

int numSub (char* s) {
    const long long mod = 1e9 + 7;
    long long cnt = 0, ans = 0;
    for (int i = 0; s [i] != '\0'; i++) {
        const char c = s [i];
        ans += (-(c == '0') & cnt * (cnt + 1) / 2);
        cnt = (-(c != '0') & cnt + 1);
    }
    ans += cnt * (cnt + 1) / 2;
    return ans % mod;
}