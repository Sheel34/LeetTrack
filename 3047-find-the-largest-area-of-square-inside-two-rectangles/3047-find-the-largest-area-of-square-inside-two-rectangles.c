long long largestSquareArea (int** bottomLeft, int bottomLeftSize, int* bottomLeftColSize, int** topRight, int topRightSize, int* topRightColSize) {
    long long maxSide = 0;
    int n = bottomLeftSize;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int x1 = fmax (bottomLeft [i] [0], bottomLeft [j] [0]);
            int y1 = fmax (bottomLeft [i] [1], bottomLeft [j] [1]);
            int x2 = fmin (topRight [i] [0], topRight [j] [0]);
            int y2 = fmin (topRight [i] [1], topRight [j] [1]);
            long width = x2 - x1;
            long height = y2 - y1;
            if (width > 0 && height > 0) {
                long side = fmin (width, height);
                maxSide = fmax (maxSide, side);
            }
        }
    }
    return maxSide * maxSide;
}