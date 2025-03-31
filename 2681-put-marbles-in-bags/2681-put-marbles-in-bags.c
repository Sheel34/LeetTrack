int compare (const void* a, const void* b) {
    return *(int*) a - *(int*) b;
}

long long putMarbles (int* weights, int weightsSize, int k) {
    if (k == 1)
        return 0;
    int n = weightsSize - 1;
    int* weight_all = (int*) malloc (n * sizeof (int));
    for (int i = 0; i < n; i++)
        weight_all [i] = weights [i] + weights [i + 1];
    qsort (weight_all, n, sizeof (int), compare);
    long long maxValue = 0, minValue = 0;
    for (int i = 0; i < k - 1; i++) {
        maxValue += weight_all [n - 1 - i];
        minValue += weight_all [i];
    }
    free (weight_all);
    return maxValue - minValue;
}