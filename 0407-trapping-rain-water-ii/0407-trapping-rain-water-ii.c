typedef struct { int x, y, h; } Cell;
typedef struct { Cell* cells; int size; } Heap;

Heap* createHeap (int capacity) {
    Heap* heap = malloc (sizeof (Heap));
    heap -> cells = malloc (capacity * sizeof (Cell));
    return heap -> size = 0, heap;
}

void push (Heap* heap, int x, int y, int h) {
    int i = heap -> size++;
    while (i && h < heap -> cells [(i - 1) / 2].h) heap -> cells [i] = heap -> cells [(i - 1) / 2], i = (i - 1) / 2;
    heap -> cells [i] = (Cell) {x, y, h};
}

Cell pop (Heap* heap) {
    Cell root = heap -> cells [0], last = heap -> cells [--heap -> size];
    int i, child;
    for (i = 0; (child = 2 * i + 1) < heap -> size; i = child) {
        if (child + 1 < heap -> size && heap -> cells [child].h > heap -> cells [child + 1].h) child++;
        if (last.h <= heap -> cells [child].h) break;
        heap -> cells [i] = heap -> cells[child];
    }
    return heap -> cells [i] = last, root;
}

int trapRainWater (int** heightMap, int heightMapSize, int* heightMapColSize) {
    int m = heightMapSize, n = *heightMapColSize, visited [m] [n], water = 0, maxHeight = 0;
    if (m < 3 || n < 3) return 0;
    memset (visited, 0, sizeof (visited));
    Heap* heap = createHeap (m * n);
    for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) if (i == 0 || i == m - 1 || j == 0 || j == n - 1) push (heap, i, j, heightMap [i] [j]), visited [i] [j] = 1;
    int dirs [4] [2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    while (heap -> size) {
        Cell cell = pop (heap);
        maxHeight = cell.h > maxHeight ? cell.h : maxHeight;
        for (int i = 0; i < 4; i++) {
            int x = cell.x + dirs [i] [0], y = cell.y + dirs [i] [1];
            if (x >= 0 && x < m && y >= 0 && y < n && !visited [x] [y]) visited [x] [y] = 1, heightMap [x] [y] < maxHeight ? (water += maxHeight - heightMap [x] [y], push(heap, x, y, maxHeight)) : push (heap, x, y, heightMap [x] [y]);
        }
    }
    free (heap -> cells), free (heap);
    return water;
}