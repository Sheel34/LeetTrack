#define BIT_VISITED 0x80000000
#define VALUE_MASK  0x7FFFFFFF

struct GridRecord {
    short sCol;
    short sRow;
};

void HeapifyDown (struct GridRecord* pstStart, struct GridRecord* pstEnd, struct GridRecord* pstCurr, int** ppnMoveTime) {
    struct GridRecord* pstChild = 1 + pstStart + ((pstCurr - pstStart) << 1);
    if (pstChild <= pstEnd) {
        if (pstChild < pstEnd) {
            struct GridRecord* pstNext = 1 + pstChild;
            if ((VALUE_MASK & ppnMoveTime [pstNext -> sRow] [pstNext -> sCol]) < (VALUE_MASK & ppnMoveTime [pstChild -> sRow] [pstChild -> sCol])) pstChild++;
        }

        if ((VALUE_MASK & ppnMoveTime [pstChild -> sRow] [pstChild-> sCol]) < (VALUE_MASK & ppnMoveTime [pstCurr -> sRow] [pstCurr -> sCol])) {
            pstChild -> sCol ^= pstCurr -> sCol;
            pstCurr -> sCol ^= pstChild -> sCol;
            pstChild -> sCol ^= pstCurr -> sCol;
            pstChild -> sRow ^= pstCurr -> sRow;
            pstCurr -> sRow ^= pstChild -> sRow;
            pstChild -> sRow ^= pstCurr -> sRow;
            HeapifyDown (pstStart, pstEnd, pstChild, ppnMoveTime);
        }
    }
}

void HeapifyUp (struct GridRecord* pstStart, struct GridRecord* pstCurr, int** ppnMoveTime) {
    if (pstStart < pstCurr) {
        struct GridRecord* pstParent = pstStart + ((-1 + pstCurr - pstStart) >> 1);
        if ((VALUE_MASK & ppnMoveTime [pstCurr -> sRow] [pstCurr -> sCol]) < (VALUE_MASK&ppnMoveTime [pstParent -> sRow] [pstParent -> sCol])) {
            pstCurr -> sCol ^= pstParent -> sCol;
            pstParent -> sCol ^= pstCurr -> sCol;
            pstCurr -> sCol ^= pstParent -> sCol;
            pstCurr -> sRow ^= pstParent -> sRow;
            pstParent -> sRow ^= pstCurr -> sRow;
            pstCurr -> sRow ^= pstParent -> sRow;
            HeapifyUp (pstStart, pstParent, ppnMoveTime);
        }
    }
}

int minTimeToReach (int** moveTime, int moveTimeSize, int* moveTimeColSize) {
    struct GridRecord astGrid [moveTimeSize * (*moveTimeColSize)];
    struct GridRecord* pstGrid = astGrid;
    pstGrid -> sCol = 0;
    (pstGrid++) -> sRow = 0;
    moveTime [0] [0] = BIT_VISITED;
    int nRet = 0;
    short sMoveTimeSize = -1 + moveTimeSize, sMoveTimeColSize = -1 + *moveTimeColSize;
    while (astGrid < pstGrid) {
        char cMove = (astGrid -> sCol + astGrid -> sRow) % 2 ? 2 : 1;
        int nTime = VALUE_MASK & moveTime [astGrid -> sRow] [astGrid -> sCol];
        if (astGrid -> sRow) {
            short sNextRow = -1 + astGrid -> sRow;
            int* pnMoveTime = astGrid -> sCol + moveTime [sNextRow];
            if (0 <= *pnMoveTime) {
                if (nTime > *pnMoveTime) *pnMoveTime = nTime;
                *pnMoveTime += cMove;
                *pnMoveTime |= BIT_VISITED;
                pstGrid -> sCol = astGrid -> sCol;
                pstGrid -> sRow = sNextRow;
                HeapifyUp (astGrid, pstGrid++, moveTime);
            }
        }
        if (astGrid -> sCol) {
            short sNextCol = -1 + astGrid -> sCol;
            int* pnMoveTime = sNextCol + moveTime [astGrid -> sRow];
            if (0 <= *pnMoveTime) {
                if (nTime > *pnMoveTime) *pnMoveTime = nTime;
                *pnMoveTime += cMove;
                *pnMoveTime |= BIT_VISITED;
                pstGrid -> sCol = sNextCol;
                pstGrid -> sRow = astGrid -> sRow;
                HeapifyUp (astGrid, pstGrid++, moveTime);
            }
        }
        if (sMoveTimeColSize > astGrid -> sCol) {
            short sNextCol = 1 + astGrid -> sCol;
            int* pnMoveTime = sNextCol + moveTime [astGrid -> sRow];
            if (0 <= *pnMoveTime) {
                if (nTime > *pnMoveTime) *pnMoveTime = nTime;
                *pnMoveTime += cMove;
                if (sMoveTimeColSize == sNextCol && sMoveTimeSize == astGrid -> sRow) {
                    nRet = *pnMoveTime;
                    break;
                }
                *pnMoveTime |= BIT_VISITED;
                pstGrid -> sCol = sNextCol;
                pstGrid -> sRow = astGrid -> sRow;
                HeapifyUp (astGrid, pstGrid++, moveTime);
            }
        }
        if (sMoveTimeSize > astGrid -> sRow) {
            short sNextRow = 1 + astGrid -> sRow;
            int* pnMoveTime = astGrid -> sCol + moveTime [sNextRow];
            if (0 <= *pnMoveTime) {
                if (nTime > *pnMoveTime) *pnMoveTime = nTime;
                *pnMoveTime += cMove;
                if (sMoveTimeSize == sNextRow && sMoveTimeColSize == astGrid -> sCol) {
                    nRet = *pnMoveTime;
                    break;
                }
                *pnMoveTime |= BIT_VISITED;
                pstGrid -> sCol = astGrid -> sCol;
                pstGrid -> sRow = sNextRow;
                HeapifyUp (astGrid, pstGrid++, moveTime);
            }
        }
        astGrid -> sCol = (--pstGrid) -> sCol;
        astGrid -> sRow = pstGrid -> sRow;
        HeapifyDown (astGrid, -1 + pstGrid, astGrid, moveTime);
    }
    return nRet;
}