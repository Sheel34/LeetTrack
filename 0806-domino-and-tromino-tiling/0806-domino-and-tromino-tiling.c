int MODVAL = 1000000007;
static int answers [1000] = {0};

int numTilings (int n) {
    if (answers [n - 1] != 0)
        return answers [n - 1];
    if (n <= 3)
        return n == 3 ? 5 : n;
    answers [n - 1] = (int) (((long) numTilings (n - 1) * 2 + numTilings (n - 3)) % MODVAL);
    return answers [n - 1];
}