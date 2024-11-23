

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char** rotateTheBox(char** box, int boxSize, int* boxColSize, int* returnSize, int** returnColumnSizes){

    int c = *boxColSize;
    *returnSize = c;
    *returnColumnSizes = (int*) malloc (c * sizeof (int));
    char** rotate = (char**) malloc (c * sizeof (char*));

    for (register i = 0; i < c; i++) {
        rotate [i] = (char*) malloc (boxSize * sizeof (char));
        memset (rotate[i], '.', boxSize);
        (*returnColumnSizes) [i] = boxSize;
    }

    for (register int i = 0; i < boxSize; i++) {
        int bottom = c - 1;
        char* row = box [i];
        for (register int j = c - 1; j >= 0; j--) {
            if (row [j] == '#') {
                rotate [bottom] [boxSize - 1 - i] = '#';
                bottom--;
            } else if (row [j] == '*') {
                rotate [j] [boxSize - 1 - i] = '*';
                bottom = j - 1;
            }
        }
    }
    return rotate;
}