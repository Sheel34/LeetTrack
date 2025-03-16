long long repairCars (int* ranks, int ranksSize, int cars) {
    long long minRank = 100;
    for (int i = 0; i < ranksSize; i++) {
        if (ranks [i] < minRank)
        minRank = ranks [i];
    }
    long long r = minRank * cars * cars, l = minRank * (cars / ranksSize) * (cars / ranksSize), m;
    while (l < r) {
        m = (r + l) / 2;
        long long carCnt = 0;
        for (int i = 0; i < ranksSize && carCnt < cars; i++)
        carCnt += sqrt (m / ranks [i]);
        if (carCnt >= cars)
        r = m;
        else
        l = m + 1;
    }
    return l;
}