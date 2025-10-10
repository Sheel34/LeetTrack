int maximumEnergy (int* energy, int energySize, int k) {
    int dp [energySize];
    int result = INT_MIN;
    for (int i = energySize - 1; i >= 0; --i) {
        int next = (i + k < energySize) ? dp [i + k] : 0;
        dp [i] = energy [i] + next;
        result = fmax (dp [i], result);
    }
    return result;
}