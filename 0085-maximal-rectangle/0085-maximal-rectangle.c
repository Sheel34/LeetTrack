int findMaxArea (int* cols, int colsSize) {
    int n = colsSize + 1;
    int stack [n];
    int top = -1;
    int maxArea = 0;
    for (int i = 0; i < n; i++) {
        int currHeight = (i == colsSize) ? 0 : cols [i];
        while (top > -1 && currHeight < cols [stack [top]]) {
            int height = cols [stack [top--]];
            int width;
            if (top < 0)
                width = i;
            else
                width = i - stack [top] - 1;
            int area = height * width;
            maxArea = (area > maxArea) ? area : maxArea;
        }
        stack [++top] = i;
    }
    return maxArea;
}

int maximalRectangle (char** matrix, int matrixSize, int* matrixColSize) {
    int cols = matrixColSize [0];
    int heights [cols];
    for (int i = 0; i < cols; i++)
        heights [i] = 0;
    int max = 0;
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < cols; j++) {
            heights [j] = (matrix [i] [j] == '0') ? 0 : heights [j] + (int) (matrix [i] [j] - '0');
        }
        int currentArea = findMaxArea (heights, cols);
        max = (max > currentArea) ? max : currentArea;
    }
    return max;
}