long long trans_t [26] [26];
const int MOD = 1e9 + 7;

void multiply (long long x [26] [26],long long y [26] [26]) {
    int i, j, k;
    long long ret [26] [26];
    memset (ret, 0, sizeof (ret));
    for (i = 0; i < 26; i++)
        for (k = 0; k < 26; k++)
            for (j = 0; j < 26; j++)
                ret [i] [j] = (ret [i] [j] + x [i] [k] * y [k] [j]) % MOD;
    memcpy (x, ret, sizeof (ret));
}

void power (long long base [26] [26],int pow) {
    int i;
    long long ret [26] [26];
    memset (ret, 0, sizeof (ret));
    for (i = 0; i < 26; i++)
        ret [i] [i] = 1;
    while (pow) {
        if (pow & 1)
            multiply (ret, base);
        multiply (base, base);
        pow >>= 1;
    }
    memcpy (trans_t, ret, sizeof (ret));
}

int lengthAfterTransformations (char* s, int t, int* nums, int numsSize) {
    int i, j, len;
    long long list [26] = {0};
    len = (int) strlen (s);
    for (i = 0; i < len; i++)
        list [s [i] - 'a']++;
    long long trans [26] [26];
    memset (trans, 0, sizeof (trans));
    for (i = 0; i < 26; i++)
        for (j = 1; j <= nums [i]; j++)
            trans [i] [(i + j) % 26]++;
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++)
            trans [i] [j] %= MOD;
    }
    power (trans, t);
    long long sum = 0;
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++)
            sum += trans_t [i] [j] * list [i];
        sum %= MOD;
    }
    return sum % MOD;
}