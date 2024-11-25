#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define TARGET "123450"
#define MAX_STATES 720
#define BOARD_SIZE 6

typedef struct {
    char state [7];
    int moves;
} BoardState;

typedef struct {
    BoardState* items;
    int front;
    int rear;
    int size;
} Queue;

typedef struct Node {
    char state [7];
    struct Node* next;
} Node;

typedef struct {
    Node* table [MAX_STATES];
} HashSet;

HashSet* createHashSet () {
    HashSet* set = (HashSet*) malloc (sizeof (HashSet));
    for (int i = 0; i < MAX_STATES; i++) {
        set -> table [i] = NULL;
    }
    return set;
}

int hashString (const char* str) {
    int hash = 0;
    for (int i = 0; str [i]; i++) {
        hash = (hash * 31 + str [i]) % MAX_STATES;
    }
    return hash;
}

bool contains (HashSet* set, const char* state) {
    int hash = hashString (state);
    Node* current = set -> table [hash];
    while (current != NULL) {
        if (strcmp (current -> state, state) == 0) {
            return true;
        }
        current = current -> next;
    }
    return false;
}

void add (HashSet* set, const char* state) {
    if (!contains (set, state)) {
        int hash = hashString (state);
        Node* newNode = (Node*) malloc (sizeof (Node));
        strcpy (newNode -> state, state);
        newNode -> next = set -> table [hash];
        set -> table [hash] = newNode;
    }
}

void freeHashSet (HashSet* set) {
    for (int i = 0; i < MAX_STATES; i++) {
        Node* current = set -> table [i];
        while (current != NULL) {
            Node* temp = current;
            current = current -> next;
            free (temp);
        }
    }
    free (set);
}

Queue* createQueue () {
    Queue* q = (Queue*) malloc (sizeof (Queue));
    q -> items = (BoardState*) malloc (MAX_STATES * sizeof (BoardState));
    q -> front = 0;
    q -> rear = -1;
    q -> size = 0;
    return q;
}

void enqueue(Queue* q, BoardState state) {
    if (q -> size < MAX_STATES) {
        q -> rear = (q -> rear + 1) % MAX_STATES;
        q -> items[q -> rear] = state;
        q -> size++;
    }
}

BoardState dequeue (Queue* q) {
    BoardState state = q -> items [q -> front];
    q -> front = (q -> front + 1) % MAX_STATES;
    q -> size--;
    return state;
}

void boardToString (int** board, char* str) {
    int index = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            str [index++] = board [i] [j] + '0';
        }
    }
    str [index] = '\0';
}

int findZero (char* str) {
    for (int i = 0; i < 6; i++) {
        if (str[i] == '0') return i;
    }
    return -1;
}

int slidingPuzzle(int** board, int boardSize, int* boardColSize) {
    
    int moves [6] [4] = {
        {1, 3, -1, -1},
        {0, 2, 4, -1},
        {1, 5, -1, -1},
        {0, 4, -1, -1},
        {1, 3, 5, -1},
        {2, 4, -1, -1}
    };
    
    HashSet* visited = createHashSet ();
    Queue* q = createQueue ();
    
    BoardState initial;
    boardToString (board, initial.state);
    initial.moves = 0;
    
    if (strcmp (initial.state, TARGET) == 0) {
        freeHashSet (visited);
        free (q -> items);
        free (q);
        return 0;
    }
    
    enqueue (q, initial);
    add (visited, initial.state);
    
    while (q -> size > 0) {
        BoardState current = dequeue (q);
        int zeroPos = findZero (current.state);
        
        for (int i = 0; i < 4 && moves [zeroPos] [i] != -1; i++) {
            char newState [7];
            strcpy (newState, current.state);
            
            int newPos = moves [zeroPos] [i];
            char temp = newState [zeroPos];
            newState [zeroPos] = newState [newPos];
            newState [newPos] = temp;
            
            if (!contains (visited, newState)) {
                if (strcmp (newState, TARGET) == 0) {
                    int result = current.moves + 1;
                    freeHashSet (visited);
                    free (q -> items);
                    free (q);
                    return result;
                }
                
                add (visited, newState);
                BoardState next;
                strcpy (next.state, newState);
                next.moves = current.moves + 1;
                enqueue (q, next);
            }
        }
    }
    
    freeHashSet (visited);
    free (q -> items);
    free (q);
    
    return -1;
}