/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

struct GridRecord {
    int nValue;
    short sCol;
    short sRow;
};

void HeapifyDownGrid (struct GridRecord* pstStart, struct GridRecord* pstEnd, struct GridRecord* pstCurr) {
    struct GridRecord* pstChild = 1 + pstStart + ((pstCurr - pstStart) << 1);
    if (pstChild <= pstEnd) {
        if (pstChild < pstEnd && pstChild -> nValue > (1 + pstChild) -> nValue) pstChild++;
        if (pstChild -> nValue < pstCurr -> nValue) {
            pstChild -> nValue ^= pstCurr -> nValue;
            pstCurr -> nValue ^= pstChild -> nValue;
            pstChild -> nValue ^= pstCurr -> nValue;
            pstChild -> sCol ^= pstCurr -> sCol;
            pstCurr -> sCol ^= pstChild -> sCol;
            pstChild -> sCol ^= pstCurr -> sCol;
            pstChild -> sRow ^= pstCurr -> sRow;
            pstCurr -> sRow ^= pstChild -> sRow;
            pstChild -> sRow ^= pstCurr -> sRow;
            HeapifyDownGrid (pstStart, pstEnd, pstChild);
        }
    }
}

void HeapifyDownQuery (int** ppnStart, int** ppnEnd, int** ppnCurr) {
    int** ppnChild = 1 + ppnStart + ((ppnCurr - ppnStart) << 1);
    if(ppnChild <= ppnEnd) {
        if (ppnChild < ppnEnd && **ppnChild > **(1 + ppnChild)) ppnChild++;
        if (**ppnChild < **ppnCurr) {
            int* pnTmp = *ppnChild;
            *ppnChild = *ppnCurr;
            *ppnCurr = pnTmp;
            HeapifyDownQuery (ppnStart, ppnEnd, ppnChild);
        }
    }
}

void HeapifyUpGrid(struct GridRecord* pstStart, struct GridRecord* pstCurr) {
    if (pstStart < pstCurr) {
        struct GridRecord* pstParent = pstStart + ((-1 + pstCurr - pstStart) >> 1);
        if (pstCurr -> nValue < pstParent -> nValue) { 
            pstCurr -> nValue ^= pstParent -> nValue;
            pstParent -> nValue ^= pstCurr -> nValue;
            pstCurr -> nValue ^= pstParent -> nValue;
            pstCurr -> sCol ^= pstParent -> sCol;
            pstParent -> sCol ^= pstCurr -> sCol;
            pstCurr -> sCol ^= pstParent -> sCol;
            pstCurr -> sRow ^= pstParent -> sRow;
            pstParent -> sRow ^= pstCurr -> sRow;
            pstCurr -> sRow ^= pstParent -> sRow;
            HeapifyUpGrid (pstStart, pstParent);
        }
    }
}

void HeapifyUpQuery (int** ppnStart, int** ppnCurr) {
    if (ppnStart < ppnCurr) {
        int** ppnParent = ppnStart + ((-1 + ppnCurr - ppnStart) >> 1);
        if (**ppnCurr < **ppnParent) {
            int* pnTmp = *ppnCurr;
            *ppnCurr = *ppnParent;
            *ppnParent = pnTmp;
            HeapifyUpQuery (ppnStart, ppnParent);
        }
    }
}

int* maxPoints (int** grid, int gridSize, int* gridColSize, int* queries, int queriesSize, int* returnSize) {
    *returnSize = queriesSize;
    int* pnRet = queries;
    int* apnHeapifyQuery [queriesSize];
    int** ppnHeapifyQuery = apnHeapifyQuery;
    *ppnHeapifyQuery = queries;
    while(--queriesSize) {
        *(++ppnHeapifyQuery) = ++queries;
        HeapifyUpQuery (apnHeapifyQuery, ppnHeapifyQuery);
    }
    short sGridSize = gridSize, sGridColSize = *gridColSize;
    int nSize = (sGridSize--) * (sGridColSize--);
    struct GridRecord astGrid [nSize];
    struct GridRecord* pstGrid = astGrid;
    pstGrid -> nValue = **grid;
    pstGrid -> sCol = 0;
    (pstGrid++) -> sRow = 0;
    **grid = -(**grid);
    int nCount = 0;
    while (astGrid < pstGrid) {
        while (apnHeapifyQuery <= ppnHeapifyQuery && **apnHeapifyQuery <= astGrid -> nValue) {
            **apnHeapifyQuery = nCount;
            *apnHeapifyQuery = *ppnHeapifyQuery;
            HeapifyDownQuery (apnHeapifyQuery, --ppnHeapifyQuery, apnHeapifyQuery);
        }
        if (ppnHeapifyQuery < apnHeapifyQuery) break;
        nCount++;
        short sCol = astGrid -> sCol, sRow = astGrid -> sRow;
        astGrid -> nValue = (--pstGrid) -> nValue;
        astGrid -> sCol = pstGrid -> sCol;
        astGrid -> sRow = pstGrid -> sRow;
        HeapifyDownGrid (astGrid, -1 + pstGrid, astGrid);
        int** ppnGrid = grid + sRow;
        int* pnGrid = *ppnGrid + sCol;
        if (sRow) {
            int* pnNew = *(-1 + ppnGrid) + sCol;
            if (0 < *pnNew) {
                pstGrid -> nValue = *pnNew;
                pstGrid -> sCol = sCol;
                pstGrid -> sRow = -1 + sRow;
                HeapifyUpGrid (astGrid, pstGrid++);

                *pnNew = -(*pnNew);
            }
        }
        if (sCol) {
            int* pnNew = -1 + pnGrid;
            if (0 < *pnNew) {
                pstGrid -> nValue = *pnNew;
                pstGrid -> sCol = -1 + sCol;
                pstGrid -> sRow = sRow;
                HeapifyUpGrid (astGrid, pstGrid++);
                *pnNew = -(*pnNew);
            }
        }
        if (sCol < sGridColSize) {
            int* pnNew = 1 + pnGrid;
            if (0 < *pnNew) {
                pstGrid -> nValue = *pnNew;
                pstGrid -> sCol = 1 + sCol;
                pstGrid -> sRow = sRow;
                HeapifyUpGrid (astGrid, pstGrid++);
                *pnNew = -(*pnNew);
            }
        }
        if (sRow < sGridSize) {
            int* pnNew = *(1 + ppnGrid) + sCol;
            if (0 < *pnNew) {
                pstGrid -> nValue = *pnNew;
                pstGrid -> sCol = sCol;
                pstGrid -> sRow = 1 + sRow;
                HeapifyUpGrid (astGrid, pstGrid++);
                *pnNew = -(*pnNew);
            }
        }
    }
    while (apnHeapifyQuery <= ppnHeapifyQuery) **(ppnHeapifyQuery--) = nCount;
    return pnRet;
}