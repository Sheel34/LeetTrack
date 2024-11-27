/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

void updateDistances (int** graph, int* graphSizes, int current, int* distances, int n) 
{
    int newDist = distances [current] + 1;

    for (int i = 0; i < graphSizes [current]; i++) {
        int neighbor = graph [current][i];
        if (distances [neighbor] <= newDist) continue;

        distances [neighbor] = newDist;
        updateDistances (graph, graphSizes, neighbor, distances, n);
    }
}

int* shortestDistanceAfterQueries (int n, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    
    *returnSize = queriesSize;
    int* distances = (int*) malloc (n * sizeof(int));
    int** graph = (int**) malloc (n * sizeof(int*));
    int* graphSizes = (int*) malloc (n * sizeof(int));
    int* answer = (int*) malloc (queriesSize * sizeof(int));

    for (int i = 0; i < n; i++) {
        distances [i] = n - 1 - i;
    }

    for (int i = 0; i < n; i++) {
        graph [i] = (int*) malloc (n * sizeof (int));
        graphSizes [i] = 0;
    }

    for (int i = 0; i + 1 < n; i++) {
        graph [i + 1] [graphSizes [i + 1]++] = i;
    }

    for (int i = 0; i < queriesSize; i++) {
        int source = queries [i] [0];
        int target = queries [i] [1];

        graph [target] [graphSizes [target]++] = source;
        distances [source] = distances [source] < distances [target] + 1 ? distances [source] : distances [target] + 1;
        updateDistances (graph, graphSizes, source, distances, n);

        answer [i] = distances [0];
    }

    for (int i = 0; i < n; i++) {
        free (graph [i]);
    }
    free (graph);
    free (graphSizes);

    return answer;
}