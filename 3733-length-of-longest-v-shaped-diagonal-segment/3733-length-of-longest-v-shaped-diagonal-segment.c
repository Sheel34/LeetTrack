typedef enum { uL = 0, uR, dR, dL } Direction; // u:up d:down L:left R:right

const Direction nextDir[4] = {uR, dR, dL, uL}; // mapping for clockwise 90-degree turn

const int vStep[4] = {-1, -1, 1, 1}, hStep[4] = {-1, 1, 1, -1}; // vertical and horizontal step length for each direction

typedef struct {
    short len[2][4];
} State;

int dfs (int M, int N, int **grid, State mem [M] [N], int i, int j, Direction dir, bool turnable, int nextNum) {
    if (mem [i] [j].len [turnable] [dir])
        return mem [i] [j].len [turnable] [dir];
    if (turnable) {
        Direction dir1 = nextDir [dir];
        int len1 = 1, i1 = i + vStep [dir1], j1 = j + hStep [dir1];
        if (i1 >= 0 && j1 >= 0 && i1 < M && j1 < N && grid [i1] [j1] == nextNum)
        len1 += dfs (M, N, grid, mem, i1, j1, dir1, false, 2 - nextNum);
        int len2 = 1, i2 = i + vStep [dir], j2 = j + hStep [dir];
        if (i2 >= 0 && j2 >= 0 && i2 < M && j2 < N && grid [i2] [j2] == nextNum)
        len2 += dfs (M, N, grid, mem, i2, j2, dir, true, 2 - nextNum);
        int len = len1 > len2 ? len1 : len2;
        mem [i] [j].len [true] [dir] = len;
        return len;
    } else {
        int len = 1, i1 = i + vStep [dir], j1 = j + hStep [dir];
        if (i1 >= 0 && j1 >= 0 && i1 < M && j1 < N && grid [i1] [j1] == nextNum)
        len += dfs (M, N, grid, mem, i1, j1, dir, false, 2 - nextNum);
        mem [i] [j].len [false] [dir] = len;
        return len;
    }
}

int lenOfVDiagonal (int** grid, int gridSize, int* gridColSize) {
    int M = gridSize, N = *gridColSize, rs = 0;
    State mem [M] [N];
    memset (mem, 0, sizeof (mem));
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
        if (grid [i] [j] == 1)
            for (int dir = 0; dir < 4; dir++) {
            int len = dfs (M, N, grid, mem, i, j, dir, true, 2);
            rs = len > rs ? len : rs;
            }
    return rs;
}