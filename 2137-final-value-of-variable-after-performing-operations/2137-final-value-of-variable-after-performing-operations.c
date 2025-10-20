int finalValueAfterOperations (char** operations, int operationsSize) {
    int x = 0;
    for (int i = 0; i < operationsSize; i++)
        x += 44 - operations [i] [1];
    return x;
}