int countNegatives (int** grid, int gridSize, int* gridColSize) {
    int count = 0;
    for (int i = 0, j = *gridColSize - 1; i < gridSize && j >= 0;) {
        if (grid [i] [j] < 0) {
            count += (gridSize - i);
            j--;
        }
        else i++;
    }
    return count;
}