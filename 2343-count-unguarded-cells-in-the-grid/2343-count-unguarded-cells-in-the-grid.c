typedef enum {
    RIGHT = 0b0001000,
    UP = 0b0010000,
    LEFT = 0b0100000,
    DOWN = 0b1000000
} DirectionMask;

typedef enum {
    UNGUARDED = 0b000,
    GUARD = 0b001,
    WALL = 0b010,
    GUARDED = 0b100
} CellTypeMask;

const int DIRECTIONS[4][4] = {
    {0, 1, RIGHT, LEFT},   // move right
    {-1, 0, UP, DOWN},     // move up
    {0, -1, LEFT, RIGHT},  // move left
    {1, 0, DOWN, UP}       // move down
};

int countUnguarded(int m, int n, int** guards, int guardsSize, int* guardsColSize, int** walls, int wallsSize, int* wallsColSize) {
    
    int grid [m] [n];

     // initializing to all unguarded
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            grid[i][j] = UNGUARDED;
        }
    }
    // placing guards
    for (int i = 0; i < guardsSize; ++i) {
        int row = guards[i][0];
        int col = guards[i][1];
        grid[row][col] = GUARD;
    }
    // placing walls
    for (int i = 0; i < wallsSize; ++i) {
        int row = walls[i][0];
        int col = walls[i][1];
        grid[row][col] = WALL;
    }

    // for each guard, mark guarded cells
    for (int guardIndex = 0; guardIndex < guardsSize; ++guardIndex) {
        int guardRow = guards[guardIndex][0];
        int guardCol = guards[guardIndex][1];
        for (int directionIndex = 0; directionIndex < 4; ++directionIndex) {
            int dRow = DIRECTIONS[directionIndex][0];
            int dCol = DIRECTIONS[directionIndex][1];
            int dirMask = DIRECTIONS[directionIndex][2];
            int oppDirMask = DIRECTIONS[directionIndex][3];

            int row = guardRow + dRow;
            int col = guardCol + dCol;
            while (0 <= row && row < m && 0 <= col && col < n) {
                int cell = grid[row][col];
                // if cell is a guard or a wall, then progress is blocked, and we break
                if ((cell & GUARD) || (cell & WALL)) {
                    break;
                }
                // if this cell is known to be guarded by traversing the opposite direction,
                // then we don't need to keep progressing because we know all cells after this
                // will be guarded as well
                if (cell & oppDirMask) {
                    break;
                }
                grid[row][col] |= GUARDED;
                grid[row][col] |= dirMask;
                row += dRow;
                col += dCol;
            }
        }
    }

    int unguardedCount = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!grid[i][j]) {
                ++unguardedCount;
            }
        }
    }

    return unguardedCount;
}