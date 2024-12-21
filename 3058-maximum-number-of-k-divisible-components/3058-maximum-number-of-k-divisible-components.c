#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct {
    Node** adj;
    int* values;
    int n;
    int ans;
} Tree;

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void addEdge(Tree* tree, int u, int v) {
    Node* node1 = createNode(v);
    node1->next = tree->adj[u];
    tree->adj[u] = node1;

    Node* node2 = createNode(u);
    node2->next = tree->adj[v];
    tree->adj[v] = node2;
}

long long helper(int node, int* values, bool* visited, Tree* tree, int k) {
    if (visited[node]) {
        return 0;
    }
    visited[node] = true;

    long long sum = values[node];
    Node* neighbor = tree->adj[node];
    while (neighbor) {
        sum += helper(neighbor->value, values, visited, tree, k);
        neighbor = neighbor->next;
    }

    if (sum % k == 0) {
        tree->ans++;
        return 0; 
    }

    return sum;
}

int maxKDivisibleComponents(int n, int** edges, int edgesSize, int* edgesColSize, int* values, int valuesSize, int k) {
    Tree tree;
    tree.n = n;
    tree.values = values;
    tree.ans = 0;

    tree.adj = (Node**)malloc(n * sizeof(Node*));
    for (int i = 0; i < n; i++) {
        tree.adj[i] = NULL;
    }

    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        addEdge(&tree, u, v);
    }

    bool* visited = (bool*)calloc(n, sizeof(bool));

    helper(0, values, visited, &tree, k);

    free(visited);
    for (int i = 0; i < n; i++) {
        Node* temp = tree.adj[i];
        while (temp) {
            Node* toDelete = temp;
            temp = temp->next;
            free(toDelete);
        }
    }
    free(tree.adj);

    return tree.ans;
}
