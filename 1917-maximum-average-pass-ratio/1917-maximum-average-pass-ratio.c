typedef struct {
    double gain;
    int pass, total;
} Class;

double Gain (int pass, int total) {
    return (double) (pass + 1) / (total + 1) - (double) pass / total;
}

void swap (Class* a, Class* b) {
    Class temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyDown (Class* heap, int n, int i) {
    int largest = i;
    int l = 2 * i + 1, r = 2 * i + 2;
    if (l < n && heap [l].gain > heap [largest].gain) largest = l;
    if (r < n && heap [r].gain > heap [largest].gain) largest = r;
    if (largest != i) {
        swap (&heap [i], &heap [largest]);
        heapifyDown (heap, n, largest);
    }
}

void heapifyUp (Class* heap, int i) {
    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap [p].gain >= heap [i].gain) break;
        swap (&heap [p], &heap [i]);
        i = p;
    }
}

Class heapPop (Class* heap, int* n) {
    Class top = heap [0];
    heap [0] = heap [--(*n)];
    heapifyDown (heap, *n, 0);
    return top;
}

void heapPush (Class* heap, int* n, Class val) {
    heap [(*n)++] = val;
    heapifyUp (heap, *n - 1);
}

double maxAverageRatio (int** classes, int classesSize, int* classesColSize, int extraStudents) {
    Class* heap = (Class*) malloc ((classesSize + extraStudents) * sizeof (Class));
    int heapSize = 0;
    double sum = 0.0;
    for (int i = 0; i < classesSize; i++) {
        int p = classes [i] [0], t = classes [i] [1];
        sum += (double) p / t;
        heapPush (heap, &heapSize, (Class) {Gain (p, t), p, t});
    }
    while (extraStudents-- > 0) {
        Class top = heapPop (heap, &heapSize);
        sum -= (double) top.pass / top.total;
        top.pass++; top.total++;
        sum += (double) top.pass / top.total;
        top.gain = Gain (top.pass, top.total);
        heapPush (heap, &heapSize, top);
    }
    free (heap);
    return sum / classesSize;
}