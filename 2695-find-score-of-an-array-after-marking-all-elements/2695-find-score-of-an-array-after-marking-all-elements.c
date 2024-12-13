typedef struct {
    int value;
    int index;
} Element;

int compare (const void* a, const void* b) {
    Element* elemA = (Element*) a;
    Element* elemB = (Element*) b;
    if (elemA -> value == elemB -> value) {
        return elemA -> index - elemB -> index;
    }
    return elemA -> value - elemB -> value;
}

long long findScore (int* nums, int numsSize) {
    Element* elements = (Element*) malloc (numsSize * sizeof (Element));
    for (int i = 0; i < numsSize; i++) {
        elements [i].value = nums [i];
        elements [i].index = i;
    }
    
    qsort (elements, numsSize, sizeof (Element), compare);

    bool* visited = (bool*) calloc (numsSize, sizeof (bool));
    long long score = 0;

    for (int i = 0; i < numsSize; i++) {
        int index = elements [i].index;

        if (visited [index]) continue;

        score += elements [i].value;

        visited [index] = true;
        if (index > 0) visited [index - 1] = true;
        if (index < numsSize - 1) visited [index + 1] = true;
    }

    free (elements);
    free (visited);

    return score;
}