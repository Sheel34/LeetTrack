#define MOD 1000000007

int numberOfWays (char* corridor) {
    long long zero = 0;
    long long one = 0;
    long long two = 1;
    for (int i = 0; corridor [i] != '\0'; i++) {
        if (corridor [i] == 'S') {
            zero = one;
            long long temp = one;
            one = two;
            two = temp;
        } else
            two = (two + zero) % MOD;
    }
    return zero;
}