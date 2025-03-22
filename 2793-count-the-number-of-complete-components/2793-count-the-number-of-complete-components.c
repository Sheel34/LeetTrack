int *connected_component_array(int node, int *visited, int** edges, int edgesSize, int *subGraphVertex) {
    visited [node] = 1;
    subGraphVertex [node] = 1;
    for (int i = 0 ; i < edgesSize; i++) {
        if (edges [i] [0] == node && visited [edges [i] [1]] != 1)
            connected_component_array (edges [i] [1], visited, edges, edgesSize,subGraphVertex);
        if (edges [i] [1] == node && visited [edges [i] [0]] != 1)
            connected_component_array (edges [i] [0], visited, edges, edgesSize, subGraphVertex);
    }
    return subGraphVertex;
}

int check_degree(int *subGraphVertex, int** edges, int edgesSize, int n) {
    int total_vertex = 0;
    for (int i = 0; i < n; i++)
        if (subGraphVertex [i] == 1)
            total_vertex = total_vertex + 1;
    for (int i = 0; i < n; i++){
        int neighbours = 0;
        if (subGraphVertex [i] == 1) {
            int node = i;
            for(int j = 0 ; j < edgesSize; j++)
                if (edges [j] [0] == node || edges [j] [1] == node)
                    neighbours = neighbours + 1;
            if (neighbours != total_vertex - 1)
                return 0;
        }
    }
    return 1;
}

int countCompleteComponents (int n, int** edges, int edgesSize, int* edgesColSize) {
    int count = 0;
    int *visited;
    visited = (int*) (malloc (n * sizeof (int)));
    for (int i = 0; i < n; i++) visited [i] = 0;
    for (int i = 0; i < n; i++) {
        if (visited [i] != 1) {
            int *subGraphVertex;
            subGraphVertex = (int*) (malloc (n * sizeof (int)));
            for (int i = 0; i < n; i++) subGraphVertex [i] = -1; 
            subGraphVertex = connected_component_array (i,visited, edges, edgesSize, subGraphVertex);
            if (check_degree (subGraphVertex,edges, edgesSize,n))
                count = count + 1;
        }
    }
    return count;
}