int closestMeetingNode(int* edges, int edgesSize, int node1, int node2) {
    int n = edgesSize, dist[n];
    int minDist = INT_MAX, index = -1;
    bool visited[n];
    memset(dist, -1, sizeof(dist));
    memset(visited, 0, sizeof(visited));
    int i = node1, curDist = 0;
    do {
        dist[i] = curDist++;
        visited[i] = true;
        i = edges[i];
    } while (i >= 0 && !visited[i]);
    i = node2;
    curDist = 0;
    memset(visited, 0, sizeof(visited));
    do {
        visited[i] = true;
        int nxtDist = dist[i];
        if (nxtDist >= 0) {
            if (nxtDist < curDist) nxtDist = curDist;
            if (nxtDist == minDist) {
                if (index < 0 || index > i) index = i;
            } else if (nxtDist < minDist) {
                minDist = nxtDist;
                index = i;
            }
        }
        i = edges[i];
        ++curDist;
} while (i >= 0 && !visited[i]);
    return index;
}