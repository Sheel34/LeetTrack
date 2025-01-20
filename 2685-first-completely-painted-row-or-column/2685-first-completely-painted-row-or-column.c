int firstCompleteIndex (int* arr, int arrSize, int** mat, int matSize, int* matColSize) {

    int* rawMap = calloc (matSize * matColSize [0] + 1, sizeof (int));
    int* colMap = calloc (matSize * matColSize [0] + 1, sizeof (int));
    int* rawCount = calloc (matSize, sizeof (int));
    int* colCount = calloc (matColSize [0], sizeof (int));

    for(int i = 0; i < matSize; i++) {
        for(int j = 0; j < matColSize [0]; j++){
            rawMap [mat [i] [j]] = i;
            colMap [mat [i] [j]] = j;
        }
    }

    int result = 0;
    for(; result < arrSize; result++) {
        rawCount [rawMap [arr [result]]] ++;
        colCount [colMap [arr [result]]] ++;
        if (rawCount [rawMap [arr [result]]] == matColSize [0] || colCount [colMap [arr [result]]] == matSize){
            break;
        }
    }

    free (rawMap);
    free (colMap);
    free (rawCount);
    free (colCount);
    
    return result;
}