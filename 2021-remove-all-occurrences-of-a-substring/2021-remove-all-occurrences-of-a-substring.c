char* removeOccurrences (char* s, char* part) {
    int s_len = strlen (s), part_len = strlen (part);
    char* resultStack = (char*) malloc ((s_len + 1) * sizeof (char));
    int stackSize = 0;
    char targetEndChar = part [part_len - 1];

    for (int i = 0; i < s_len; i++) {
        resultStack [stackSize++] = s [i];

        if (s [i] == targetEndChar && stackSize >= part_len) {
            int j = 0;
            while (j < part_len && resultStack [stackSize - part_len + j] == part [j]) {
                j++;
            }
            if (j == part_len) {
                stackSize -= part_len;
            }
        }
    }
    resultStack [stackSize] = '\0';
    return resultStack;
}