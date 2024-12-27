int max (int a, int b) { return a > b ? a : b; }

int maxScoreSightseeingPair (int* values, int valuesSize) {

    int ans= 0;
    int prev = values [0];

    for (int j = 1; j < valuesSize; j++) {
        ans = max (ans, prev + values [j] - j);
        prev = max (prev, values [j] + j);
    }

    return ans;
}