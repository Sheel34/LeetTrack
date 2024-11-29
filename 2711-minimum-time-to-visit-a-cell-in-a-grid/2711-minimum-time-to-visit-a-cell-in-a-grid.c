typedef struct {
    int time;
    int x;
    int y;
} Node;

typedef struct {
    Node* array;
    int size;
    int capacity;
} MinHeap;

MinHeap* createMinHeap (int capacity) {
    MinHeap* minHeap = (MinHeap*) malloc (sizeof (MinHeap));
    minHeap -> size = 0;
    minHeap -> capacity = capacity;
    minHeap -> array = (Node*) malloc (capacity * sizeof (Node));
    return minHeap;
}

void swap (Node* a, Node* b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify (MinHeap* minHeap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < minHeap -> size && minHeap -> array [left].time < minHeap -> array [smallest].time) {
        smallest = left;
    }
    if (right < minHeap -> size && minHeap -> array [right].time < minHeap -> array [smallest].time) {
        smallest = right;
    }
    if (smallest != index) {
        swap (&minHeap -> array [smallest], &minHeap -> array [index]);
        minHeapify (minHeap, smallest);
    }
}

void insertMinHeap (MinHeap* minHeap, Node node) {
    if (minHeap -> size == minHeap -> capacity) {
        return;
    }
    minHeap -> array[minHeap -> size] = node;
    int i = minHeap -> size;
    minHeap -> size++;

    while (i != 0 && minHeap -> array [(i - 1) / 2].time > minHeap -> array [i].time) {
        swap (&minHeap -> array [i], &minHeap -> array [(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

Node extractMin (MinHeap* minHeap) {
    if (minHeap -> size == 0) {
        Node emptyNode = {INT_MAX, -1, -1};
        return emptyNode;
    }
    Node root = minHeap -> array [0];
    if (minHeap -> size > 1) {
        minHeap -> array [0] = minHeap -> array [minHeap -> size - 1];
    }
    minHeap -> size--;
    minHeapify (minHeap, 0);
    return root;
}

int minimumTime (int** grid, int gridSize, int* gridColSize) {
    
    MinHeap* pq = createMinHeap (gridSize * (*gridColSize));

    int** dist = (int**) malloc (gridSize * sizeof (int*));

    for (int i = 0; i < gridSize; i++) {

        dist [i] = (int*) malloc ((*gridColSize) * sizeof (int));

        for (int j = 0; j < (*gridColSize); j++) {
            dist [i] [j] = INT_MAX;
        }
    }
    dist [0] [0] = 0;

    int dirs [4] [2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

    if (grid [0] [1] > 1 && grid [1] [0] > 1) {
        return -1;
    }

    Node start = {0, 0, 0};
    insertMinHeap (pq, start);

    while (pq -> size > 0) {
        Node current = extractMin (pq);
        if (dist [current.x] [current.y] < current.time) {
            continue;
        }
        if (current.x == gridSize - 1 && current.y == (*gridColSize) - 1) {
            return current.time;
        }
        for (int i = 0; i < 4; i++) {
            int a = current.x + dirs [i] [0];
            int b = current.y + dirs [i] [1];
            if (a >= 0 && a < gridSize && b >= 0 && b < (*gridColSize)) {
                int k = 0;
                if ((grid [a] [b] - current.time) > 1) {
                    k += (grid [a] [b] - current.time);
                    if ((grid [a] [b] - current.time) % 2 == 0) {
                        k++;
                    }
                } else {
                    k = 1;
                }
                if (dist [a] [b] > current.time + k) {
                    dist [a] [b] = current.time + k;
                    Node node = {dist [a] [b], a, b};
                    insertMinHeap (pq, node);
                }
            }
        }
    }

    return -1;

}