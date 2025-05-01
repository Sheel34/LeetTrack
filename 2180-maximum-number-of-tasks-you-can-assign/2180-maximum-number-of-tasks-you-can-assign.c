int compare (const void* a, const void* b) {
    return *(int*) a - *(int*) b;
}

bool doable (int* tasks, int* workers, int n, int m, int k, int pills, int strength) {
    static int q [50000];
    int front = 0, back = 0, t = 0;
    for (int w = m - k; w < m; ++w) {
        int limit = workers [w] + strength;
        while (t < k && tasks [t] <= limit)
            q[back++] = tasks [t++];
        if (front == back)
            return false;
        if (q [front] <= workers [w]) {
            front++;  
        } else {
            if (pills-- == 0)
                return false;
            back--;  
        }
    }
    return true;
}

int maxTaskAssign (int* tasks, int tasksSize, int* workers, int workersSize, int pills, int strength) {
    qsort (tasks, tasksSize, sizeof (int), compare);
    qsort (workers, workersSize, sizeof (int), compare);
    int lo = 0, hi = tasksSize < workersSize ? tasksSize : workersSize;
    while (lo < hi) {
        int mid = (lo + hi + 1) >> 1 ;
        if (doable (tasks, workers, tasksSize, workersSize, mid, pills, strength))
            lo = mid;
        else
            hi = mid - 1;
    }
    return lo;
}