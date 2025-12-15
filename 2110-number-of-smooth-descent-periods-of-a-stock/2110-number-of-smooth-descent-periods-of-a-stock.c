long long getDescentPeriods (int* prices, int pricesSize) {
    long long sum = 1, des = 1;
    for (int i = 1; i < pricesSize; i++) {
        des = (prices [i] + 1 == prices [i - 1]) * des + 1;
        sum += des;
    }
    return sum;
}