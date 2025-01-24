/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

bool DFS (int **graph, int *graphColSize, int *safe, int *visited, int node) {
    bool isSafe = true;

    for (int i = 0; i < graphColSize [node]; i++) {
        int neighbour = graph [node] [i];
        if (!safe [neighbour] || visited [neighbour]) {
            isSafe = false;
            break;
        }
        if (safe [neighbour] == 1) {
            continue;
        }
        visited [neighbour] = 1;
        if (DFS (graph, graphColSize, safe, visited, neighbour) == false) {
            isSafe = false;
            break;
        }
        visited [neighbour] = 0;
    }
    safe [node] = isSafe ? 1 : 0;
    return isSafe;
}

int* eventualSafeNodes (int** graph, int graphSize, int* graphColSize, int* returnSize) {
    int* safe = malloc (graphSize * sizeof (int));
    int* visited = malloc (graphSize * sizeof (int));

    for (int i = 0; i < graphSize;i++) {
        safe [i] = -1;
        visited [i] = 0;
    }

    for (int node = 0; node < graphSize; node++)
        if (safe [node] == -1) {
            visited [node] = 1;
            DFS (graph, graphColSize, safe, visited, node);
            visited [node] = 0;
        }

    int *returnArray = malloc (graphSize * sizeof (int));
    *returnSize = 0;
    for (int node = 0; node < graphSize; node++)
        if (safe [node] == 1)
            returnArray [(*returnSize)++] = node;
    
    return returnArray;
}