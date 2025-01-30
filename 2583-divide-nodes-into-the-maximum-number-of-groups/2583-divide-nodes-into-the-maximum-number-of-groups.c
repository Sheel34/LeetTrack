#define MAX_NODES 1000

typedef struct {
    int data [MAX_NODES];
    int front, rear;
} Queue;

void initQueue (Queue *q) {
    q -> front = q -> rear = 0;
}

bool isEmpty (Queue *q) {
    return q -> front == q -> rear;
}

void enqueue (Queue *q, int value) {
    q -> data [q -> rear++] = value;
}

int dequeue (Queue *q) {
    return q -> data [q -> front++];
}

bool isBipartite (int adjList [MAX_NODES] [MAX_NODES], int n, int node, int colors []) {
    Queue q;
    initQueue (&q);
    enqueue (&q, node);
    colors [node] = 0;

    while (!isEmpty (&q)) {
        int currentNode = dequeue (&q);

        for (int i = 0; i < n; i++) {
            if (adjList [currentNode] [i]) {
                if (colors [i] == colors [currentNode]) {
                    return false;
                }
                if (colors [i] == -1) {
                    colors [i] = 1 - colors [currentNode];
                    enqueue (&q, i);
                }
            }
        }
    }
    return true;
}

int getLongestShortestPath (int adjList [MAX_NODES] [MAX_NODES], int srcNode, int n) {
    Queue q;
    initQueue (&q);
    bool visited [MAX_NODES] = {false};
    enqueue (&q, srcNode);
    visited [srcNode] = true;

    int distance = 0;

    while (!isEmpty (&q)) {
        int numOfNodesInLayer = q.rear - q.front;
        for (int i = 0; i < numOfNodesInLayer; i++) {
            int currentNode = dequeue (&q);

            for (int j = 0; j < n; j++) {
                if (adjList [currentNode] [j] && !visited [j]) {
                    visited [j] = true;
                    enqueue (&q, j);
                }
            }
        }
        distance++;
    }
    return distance;
}

int getNumberOfGroupsForComponent (int adjList [MAX_NODES] [MAX_NODES], int node,
                                  int distances [], bool visited [], int n) {
    visited [node] = true;
    int maxNumberOfGroups = distances [node];

    for (int i = 0; i < n; i++) {
        if (adjList [node] [i] && !visited [i]) {
            int groupsForNeighbor =
                getNumberOfGroupsForComponent (adjList, i, distances, visited, n);
            if (groupsForNeighbor > maxNumberOfGroups) {
                maxNumberOfGroups = groupsForNeighbor;
            }
        }
    }
    return maxNumberOfGroups;
}

int magnificentSets (int n, int** edges, int edgesSize, int* edgesColSize) {
    int adjList [MAX_NODES] [MAX_NODES] = {0};
    
    for (int i = 0; i < edgesSize; i++) {
        int u = edges [i] [0] - 1;
        int v = edges [i] [1] - 1;
        adjList [u] [v] = adjList [v] [u] = 1;
    }

    int colors [MAX_NODES];
    memset (colors, -1, sizeof (colors));

    for (int node = 0; node < n; node++) {
        if (colors [node] == -1) {
            if (!isBipartite (adjList, n, node, colors)) {
                return -1;
            }
        }
    }
    int distances [MAX_NODES];
    for (int node = 0; node < n; node++) {
        distances [node] = getLongestShortestPath (adjList, node, n);
    }

    bool visited [MAX_NODES] = {false};
    int maxNumberOfGroups = 0;

    for (int node = 0; node < n; node++) {
        if (!visited [node]) {
            maxNumberOfGroups += getNumberOfGroupsForComponent (
                adjList, node, distances, visited, n);
        }
    }
    return maxNumberOfGroups;
}