struct BTreeNum {
    int size;
    struct BNodeNum* Root;
} BTreeNum;

struct BNodeNum {
    int  numId;
    void* value;
    struct BNodeNum* fatherBNode;
    struct BNodeNum* sxBNode;
    char          sxWeight;
    struct BNodeNum* dxBNode;
    char          dxWeight;
} BNodeNum;

struct BTreeNum* createBTreeNum () {
    struct BTreeNum* bTree = (struct BTreeNum*) malloc (sizeof (BTreeNum));
    if (bTree != NULL)
        memset (bTree, 0, sizeof (BTreeNum));
    return bTree;
}

struct BNodeNum* deepBNodeNum (struct BTreeNum* bTree, struct BNodeNum* bNode) {
    if (bNode != NULL) {
        if (bNode -> sxBNode != NULL)
            bNode = deepBNodeNum (bTree, bNode -> sxBNode);
        else if (bNode -> dxBNode != NULL)
            bNode = deepBNodeNum (bTree, bNode -> dxBNode);
    }
    return bNode;
}

void destroyBTreeNum (struct BTreeNum* bTree) {
    struct BNodeNum* delNode;
    struct BNodeNum* fatherNode;
    while ((delNode = deepBNodeNum (bTree, bTree -> Root)) != NULL) {
        fatherNode = delNode -> fatherBNode;
        if (fatherNode != NULL) {
            if (fatherNode -> sxBNode == delNode)
                fatherNode -> sxBNode = NULL;
            else
                fatherNode -> dxBNode = NULL;
        }
        else
            bTree -> Root = NULL;
        free (delNode);
        bTree -> size--;
    }
    free (bTree);
}

struct BNodeNum* getToInsertBNodeNum (struct BTreeNum* bTree, struct BNodeNum* bNode, int numId) {
    if (bNode != NULL) {
        if (bNode -> numId >= numId) {
            if (bNode -> sxBNode != NULL)
                bNode = getToInsertBNodeNum (bTree, bNode -> sxBNode, numId);
        }
        else if (bNode -> numId < numId) {
            if (bNode -> dxBNode != NULL)
                bNode = getToInsertBNodeNum (bTree, bNode -> dxBNode, numId);
        }
    }
    return bNode;
}

struct BNodeNum* addBNodeNum (struct BTreeNum* bTree, int numId, void* value) {
    struct BNodeNum* newBNode = NULL;
    if (bTree != NULL) {
        struct BNodeNum* deepBNode = NULL;
        newBNode = (struct BNodeNum*) malloc (sizeof (BNodeNum));
        if (newBNode != NULL) {
            memset (newBNode, 0, sizeof (BNodeNum));
            newBNode -> numId = numId;
            newBNode -> value = value;
            if (bTree -> Root == NULL) {
                bTree -> size = 1;
                bTree -> Root = newBNode;
            }
            else {
                deepBNode = getToInsertBNodeNum (bTree, bTree -> Root, numId);
                if (deepBNode -> numId >= numId) {
                    deepBNode -> sxBNode = newBNode;
                }
                else if (deepBNode -> numId < numId) {
                    deepBNode -> dxBNode = newBNode;
                }
                else {
                    free (newBNode);
                    newBNode = NULL;
                }
                if (newBNode != NULL) {
                    newBNode -> fatherBNode = deepBNode;
                    bTree -> size++;
                }
            }
        }
    }
    return newBNode;
}

struct BNodeNum* firstBNodeNum (struct BTreeNum* bTree) {
    struct BNodeNum* firstBNode = NULL;
    if (bTree != NULL) {
        if (bTree -> Root != NULL) {
            firstBNode = bTree -> Root;
            while (firstBNode -> sxBNode != NULL)
                firstBNode = firstBNode -> sxBNode;
        }
    }
    return firstBNode;
}

struct BNodeNum* nextBNodeNum (struct BTreeNum* bTree, struct BNodeNum* bNode) {
    struct BNodeNum* nextBNode = NULL;
    if (bTree != NULL) {
        if (bNode != NULL) {
            if (bNode -> dxBNode != NULL) {
                nextBNode = bNode -> dxBNode;
                while (nextBNode -> sxBNode != NULL)
                    nextBNode = nextBNode -> sxBNode;
            }
            else {
                nextBNode = bNode -> fatherBNode;
                while (nextBNode != NULL && nextBNode -> numId < bNode -> numId)
                    nextBNode = nextBNode -> fatherBNode;
            }
        }
    }
    return nextBNode;
}

struct BNodeNum* getBNodeNum2 (struct BTreeNum* bTree, struct BNodeNum* bNode, int numId) {
    if (bNode != NULL) {
        if (bNode -> numId > numId) {
            if (bNode -> sxBNode != NULL)
                bNode = getBNodeNum2 (bTree, bNode -> sxBNode, numId);
            else
                bNode = NULL;
        }
        else if (bNode -> numId < numId) {
            if (bNode -> dxBNode != NULL)
                bNode = getBNodeNum2 (bTree, bNode -> dxBNode, numId);
            else
                bNode = NULL;
        }
    }
    return bNode;
}

struct BNodeNum* getBNodeNum (struct BTreeNum* bTree, int numId) {
    if (bTree != NULL)
        return getBNodeNum2 (bTree, bTree -> Root, numId);
    return NULL;
}

void* deleteFirstBNodeNum (struct BTreeNum* bTree) {
    if (bTree == NULL)
        return NULL;
    struct BNodeNum* deleteBNode = firstBNodeNum (bTree);
    void* value = deleteBNode -> value;
    struct BNodeNum* fatherBnode = deleteBNode -> fatherBNode;
    struct BNodeNum* dxBnode = deleteBNode -> dxBNode;
    if (fatherBnode == NULL)
        bTree -> Root = dxBnode;
    else
        fatherBnode -> sxBNode = dxBnode;
    if (dxBnode != NULL)
        dxBnode -> fatherBNode = fatherBnode;
    free (deleteBNode);
    bTree -> size--;
    return value;
}

int numRabbits (int* answers, int answersSize) {
    int numRabbits = 0;
    struct BTreeNum* answersTree = createBTreeNum ();
    struct BNodeNum* bNode;
    for (int i = 0; i < answersSize; i++) {
        bNode = getBNodeNum (answersTree, answers [i]);
        if (bNode == NULL)
            bNode = addBNodeNum (answersTree, answers [i], NULL);
        bNode -> value = (void*) ((int) bNode -> value + 1);
    }
    bNode = firstBNodeNum (answersTree);
    while (bNode != NULL) {
        if (((int) bNode->value % (bNode -> numId + 1)) == 0)
            numRabbits = numRabbits + (((int) bNode -> value / (bNode -> numId + 1)) * (bNode -> numId + 1));
        else
            numRabbits = numRabbits + ((((int) bNode -> value / (bNode -> numId + 1)) + 1) * (bNode -> numId + 1));
        bNode = nextBNodeNum (answersTree, bNode);
    }
    destroyBTreeNum (answersTree);
    return numRabbits;
}