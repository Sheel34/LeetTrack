bool isOneBitCharacter (int* bits, int bitsSize) {
    int i = 0;
    for (; i < bitsSize - 1; i++)
        i += (bits [i] == 1);
    return i == bitsSize - 1;
}