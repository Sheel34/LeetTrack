#define MOD 1000000007

int dp [100001];

int count (int low, int high, int zero, int one, int len)
{
    int cnt = 0;

    if (len > high) {
        return 0;
    }
    
    if (dp [len] != -1) {
        return dp [len];
    }

    if (len >= low && len <= high) {
        cnt = 1;
    }

    cnt += (count (low, high, zero, one, len + zero) % MOD);
    cnt %= MOD;

    cnt += (count (low, high, zero, one, len + one) % MOD);
    cnt %= MOD;

    dp [len] = cnt;

    return cnt;
}

int countGoodStrings (int low, int high, int zero, int one) {

    int ans = 0;

    for (int i = 0; i <= high; i++) {
        dp [i] = -1;
    }

    ans = count (low, high, zero, one, 0);

    return ans;
}