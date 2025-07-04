char kthCharacter (long long k, int* operations, int operationsSize) {
    int c = 0; k--;
    for (int i = 0; k != 0; i++, k >>= 1) c += ((int) (k & 1) & operations [i]);
    return (char) ((c % 26) + 'a');
}