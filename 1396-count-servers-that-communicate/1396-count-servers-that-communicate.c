int countServers (int** grid, int gridSize, int* gridColSize) {
    int computer = 0;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < *gridColSize; j++) {
            if (grid [i] [j] == 1) {
                bool flag = 0;
                for (int row = 0; row < *gridColSize; row++) {
                    if (j != row && grid [i] [row] == 1) {
                        flag = 1;
                        break;
                    }
                }
                for (int col = 0; col < gridSize; col++) {
                    if (i != col && grid [col] [j] == 1) {
                        flag = 1;
                        break;
                    }
                }
                if (flag)
                    computer++;
            }
        }
    }
    return computer;
}