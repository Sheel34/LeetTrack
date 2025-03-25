#define max(a, b) ((a) > (b) ? (a) : (b))

int cmpByX (const void *a, const void *b) {
  return (*(int **) a) [0] - (*(int **) b) [0];
}

int cmpByY (const void *a, const void *b) {
  return (*(int **) a) [1] - (*(int **) b) [1];
}

bool checkValidCuts (int n, int** rectangles, int rectanglesSize, int* rectanglesColSize) {
    int preCutPosition = 0, cutNum = 0;
    qsort (rectangles, rectanglesSize, sizeof (int*), cmpByX);
    for (int i = 0; i < rectanglesSize; i++) {
        if (rectangles [i] [0] >= preCutPosition) {
            cutNum++;
            preCutPosition = rectangles [i] [2];
            if (cutNum > 2)
                return true;
        }
        else
            preCutPosition = max (preCutPosition, rectangles [i] [2]);
    }
    cutNum = 0;
    preCutPosition = 0;
    qsort (rectangles, rectanglesSize, sizeof (int*), cmpByY);
    for (int i = 0; i < rectanglesSize; i++) {
        if (rectangles [i] [1] >= preCutPosition) {
            cutNum++;
            preCutPosition = rectangles [i] [3];
            if (cutNum > 2)
                return true;
        }
        else
            preCutPosition = max (preCutPosition, rectangles [i] [3]);
    }
    return false;
}