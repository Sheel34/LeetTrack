int totalFruit (int* fruits, int fruitsSize) {
    int lastFruit = -1, secondLastFruit = -1;
    int lastCount = 0, currMax = 0, max = 0;
    for (int i = 0; i < fruitsSize; i++) {
        int fruit = fruits [i];
        if (fruit == lastFruit || fruit == secondLastFruit)
            currMax++;
        else
            currMax = lastCount + 1;
        if (fruit == lastFruit)
            lastCount++;
        else {
            lastCount = 1;
            secondLastFruit = lastFruit;
            lastFruit = fruit;
        }
        max = fmax (max, currMax);
    }
    return max;
}