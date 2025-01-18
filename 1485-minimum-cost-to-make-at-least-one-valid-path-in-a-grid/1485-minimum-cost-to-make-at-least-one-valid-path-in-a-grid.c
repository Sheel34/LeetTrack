#define MAX_STATES 10000

struct QueueNode {
    int state [2]; 
    int moves;
};

struct Queue {
    struct QueueNode data [MAX_STATES];
    int front, rear;
};

void initQueue (struct Queue* q);
int isEmpty (struct Queue* q);
void enqueue (struct Queue* q, int* state, int moves);
struct QueueNode dequeue (struct Queue* q);

void resetDp (int **hash, int m, int n) {
    int i = 0, j = 0;
    for (i = 0; i < m; i++)
    {
        for (j = 0; j  < n; j++)
            hash [i] [j] = -1;
    }
}

int minCost (int** grid, int gridSize, int* gridColSize) {
    int row = gridSize;
    int col = *gridColSize;
    int min = INT_MAX;

    int visited [100] [100] = {0};

    int** best = (int**) malloc ((row + 1) * sizeof (int*));
    for (int i = 0; i < row+1; i++)  {
        best [i] = (int*) malloc ((col + 1) * sizeof (int));
    }
   resetDp (best, row + 1, col + 1);

    struct Queue q;
    initQueue (&q);
    int initial [2] = {0,0};
    enqueue (&q, initial, 0);

    best [0] [0] = 0;
    while (!isEmpty (&q))
    {
        struct QueueNode current = dequeue (&q);
        int x = current.state [0];
        int y = current.state [1];

        int directions [5] [2] = {{0,0}, {0,1}, {0,-1}, {1,0}, {-1,0}};
        for (int i = 1; i < 5; i++) {
            uint curMove = 0;
            if (grid [x] [y] != i) {
                curMove = 1;
            }
            int next [2];
            next [0] = x + directions [i] [0];
            next [1] = y + directions [i] [1];
            uint nextMove = current.moves + curMove;
            if ((next [0] == row) && (next [1] == col) && (min < nextMove)) {
                min = nextMove;
            }
            if ((next [0] >= 0) && (next [1] >= 0) && (next [0] < row) && (next [1] < col) && ((visited [next [0]] [next [1]] == 0) || best [next [0]] [next [1]] > nextMove )) {
                best [next [0]] [next [1]] = nextMove;
                visited [next [0]] [next [1]] = 1;
                enqueue (&q, next, nextMove);
            }
        }
    }
    return best [row - 1] [col - 1];
}

void initQueue (struct Queue* q) {
    q -> front = -1;
    q -> rear = -1;
}

int isEmpty (struct Queue* q) { return (q -> front == -1 && q -> rear == -1); }

void enqueue (struct Queue* q, int* state, int moves) {
    if (isEmpty (q)) {
        q -> front = 0;
        q -> rear = 0;
    } else {
        q -> rear = (q -> rear + 1) % MAX_STATES;
    }
    q -> data [q -> rear].state [0] = state [0];
    q -> data [q -> rear].state [1] = state [1];
    q -> data [q -> rear].moves = moves;
}

struct QueueNode dequeue (struct Queue* q) {
    struct QueueNode node = q -> data [q -> front];
    if (q -> front == q -> rear) {
        q -> front = -1;
        q -> rear = -1;
    } else {
        q -> front = (q -> front + 1) % MAX_STATES;
    }
    return node;
}