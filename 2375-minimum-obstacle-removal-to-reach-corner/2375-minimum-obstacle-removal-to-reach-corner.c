typedef struct {
    int x, y;
} Pair;

int dx [] = {-1, 0, 1, 0};
int dy [] = {0, 1, 0, -1};

typedef struct Node {
    Pair data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct {
    Node* front;
    Node* rear;
} Deque;

void initDeque (Deque* dq) {
    dq -> front = dq -> rear = NULL;
}

void pushFront (Deque* dq, Pair p) {
    Node* node = (Node*) malloc (sizeof (Node));
    node -> data = p;
    node -> next = dq -> front;
    node -> prev = NULL;
    if (dq -> front) dq -> front -> prev = node;
    dq -> front = node;
    if (!dq -> rear) dq -> rear = node;
}

void pushBack (Deque* dq, Pair p) {
    Node* node = (Node*) malloc (sizeof (Node));
    node -> data = p;
    node -> next = NULL;
    node -> prev = dq -> rear;
    if (dq -> rear) dq -> rear -> next = node;
    dq -> rear = node;
    if (!dq -> front) dq -> front = node;
}

Pair popFront (Deque* dq) {
    Pair data = dq -> front -> data;
    Node* temp = dq -> front;
    dq -> front = dq -> front -> next;
    if (dq -> front) dq -> front -> prev = NULL;
    else dq -> rear = NULL;
    free (temp);
    return data;
}

bool isDequeEmpty (Deque* dq) {
    return dq -> front == NULL;
}

void freeDeque (Deque* dq) {
    while (!isDequeEmpty (dq)) {
        popFront (dq);
    }
}


int minimumObstacles (int** grid, int gridSize, int* gridColSize) {
    
    int m = gridSize, n = gridColSize [0];
    int** distance = (int**) malloc (m * sizeof (int*));
    for (int i = 0; i < m; i++) {
        distance [i] = (int*) malloc (n * sizeof (int));
        for (int j = 0; j < n; j++)
            distance [i] [j] = INT_MAX;
    }

    Deque dq;
    initDeque (&dq);
    pushFront (&dq, (Pair) {0, 0});
    distance [0] [0] = 0;

    while (!isDequeEmpty (&dq)) {
        Pair p = popFront (&dq);
        int x = p.x, y = p.y;

        for (int k = 0; k < 4; k++) {
            int nx = x + dx [k];
            int ny = y + dy [k];

            if (nx < 0 || ny < 0 || nx >= m || ny >= n) continue;

            int newDist = distance [x] [y] + grid [nx] [ny];
            if (newDist < distance [nx] [ny]) {
                distance [nx] [ny] = newDist;
                if (grid [nx] [ny] == 0)
                    pushFront(&dq, (Pair) {nx, ny});
                else
                    pushBack (&dq, (Pair) {nx, ny});
            }
        }
    }

    int result = distance [m - 1] [n - 1];

    for (int i = 0; i < m; i++) {
        free (distance [i]);
    }
    free (distance);
    freeDeque (&dq);

    return result;
}