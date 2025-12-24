int compare (const void* a, const void* b) {
    return *(int*)a - *(int*) b;
}

int minimumBoxes (int* apple, int appleSize, int* capacity, int capacitySize) {
    int sumApples = 0, count = 0, n = appleSize, m = capacitySize;
    for (int i = 0; i < n; i++)
        sumApples += apple [i];
    qsort (capacity, capacitySize, sizeof (int), compare);
    int right = m - 1;
    while (right >= 0) {
        sumApples -= capacity [right];
        count++;
        if (sumApples <= 0) break;
        right--;
    }
    return count;
}