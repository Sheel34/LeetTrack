int numEquivDominoPairs (int** dominoes, int dominoesSize, int* dominoesColSize) {
    int* map = (int*) calloc (sizeof (int), 100);
    int count = 0;
    for (int i = 0; i < dominoesSize; ++i) {
        int u = dominoes [i] [0];
        int v = dominoes [i] [1];
        int num = (u > v) ? v * 10 + u : u * 10 + v;
        count += map [num];
        map [num]++;
    }
    free (map);
    return count;
}