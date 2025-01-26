struct node {
    int val;
    struct node* next;
};

struct node* createNode (int val) {
    struct node* ret = malloc (sizeof (struct node));
    ret -> val = val;
    ret -> next = NULL;

    return ret;
}

void addNode (struct node** map, int idx, int val) {
    struct node* tmp = map [idx] -> next;
    map [idx] -> next = createNode (val);
    map [idx] -> next -> next = tmp;
}

int bfs (struct node** map, int start, int n, int skip) {
    int vis [n];
    int queue [n] [2];
    memset (vis, 0, sizeof (vis));

    int front = 0, rear = 0, maxDist = 0;
    
    vis [start] = vis [skip] = 1;
    queue [rear] [0] = start;
    queue [rear++] [1] = 0;
    
    while (front < rear) {
        int u = queue [front] [0]; 
        int distU = queue [front] [1];
        front++; 
        
        for (struct node* tmp = map [u] -> next; tmp; tmp = tmp -> next) {
            int v = tmp -> val;
            if (!vis [v]) {
                vis [v] = 1;
                int newDist = distU + 1;
                queue [rear] [0] = v;
                queue [rear++] [1] = newDist;
                maxDist = maxDist > newDist? maxDist : newDist;
            }
        }
    }
    
    return maxDist;
}

int maximumInvitations (int* favourite, int favouriteSize) {
    int* vis = calloc (favouriteSize, sizeof (int));
    struct node** map = malloc (favouriteSize * sizeof (struct node*));

    for (int i = 0; i < favouriteSize; i++) {
        map [i] = createNode (i);
    }
    for (int i = 0; i < favouriteSize; i++) {
        addNode (map, favourite [i], i);
    }
    
    int maxCycle = 0;
    int dCycle = 0;
    
    for (int i = 0; i < favouriteSize; i++) {
        if (!vis [i]) {
            int tmpVis [favouriteSize];
            memset (tmpVis, 0, sizeof (tmpVis));
            
            int curr = i;
            int dist = 0;
            
            while (!vis [curr]) {
                vis [curr] = 1;
                tmpVis [curr] = ++dist;      
                int next = favourite [curr];
                
                if(tmpVis [next] && tmpVis [next] < tmpVis [curr]) {
                    int cycleLength = dist - tmpVis [next] + 1;
                    maxCycle = maxCycle > cycleLength? maxCycle : cycleLength;
                    if(cycleLength == 2) {
                        dCycle += 2 + bfs (map, curr, favouriteSize, next) + bfs (map, next, favouriteSize, curr);
                    }
                    break;
                }       
                curr = next;
            }
        }
    }
    
    return (maxCycle > dCycle) ? maxCycle : dCycle;
}