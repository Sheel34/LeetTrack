/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** generate (int numRows, int* returnSize, int** returnColumnSizes) {
    int** a = (int **) malloc (sizeof (int*) * numRows);
    *returnSize = numRows;
    *returnColumnSizes = (int*) malloc (sizeof (int) * numRows);
    for (register int i = 0; i < numRows; i++) {
        (*returnColumnSizes) [i] = i + 1;
        a [i] = (int*) malloc (sizeof (int) * (i + 1));
        a [i] [0] = a [i] [i] = 1;
        for (register int j = 1; j <= i / 2; j++)
            a [i] [j] = a [i] [i - j] = a [i - 1] [j - 1] + a [i - 1] [j];
    }
    return a;
}