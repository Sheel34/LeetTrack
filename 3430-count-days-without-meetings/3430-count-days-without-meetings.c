typedef struct {
    int start, end;
} Interval;

int compare (const void *a, const void *b) {
    return ((Interval*) a) -> start - ((Interval*) b) -> start;
}

int countDays (int days, int** meetings, int meetingsSize, int* meetingsColSize) {
    if (meetingsSize == 0) return days;
    Interval *intervals = (Interval*) malloc (meetingsSize * sizeof (Interval));
    for (int i = 0; i < meetingsSize; i++) {
        intervals [i].start = meetings [i] [0];
        intervals [i].end = meetings [i] [1];
    }
    qsort (intervals, meetingsSize, sizeof (Interval), compare);
    int busyDays = 0;
    int mergedStart = intervals [0].start, mergedEnd = intervals [0].end;
    for (int i = 1; i < meetingsSize; i++) {
        if (intervals [i].start > mergedEnd) {
            busyDays += (mergedEnd - mergedStart + 1);
            mergedStart = intervals [i].start;
            mergedEnd = intervals [i].end;
        } else if (intervals [i].end > mergedEnd) {
            mergedEnd = intervals [i].end;
        }
    }
    busyDays += (mergedEnd - mergedStart + 1);
    free (intervals);
    return days - busyDays;
}