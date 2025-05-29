/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

typedef struct node {
  int *nexts;
  int len;
  int cap;
} node;

void addNextNode(node *n1, int n2) {
  n1->nexts[n1->len++] = n2;
  if (n1->len == n1->cap) {
    n1->cap *= 2;
    n1->nexts = realloc(n1->nexts, n1->cap * sizeof(int));
  }
}

node *restoreTree(int **edges, int edgesSize) {
  int treeSize = edgesSize + 1;
  node *nodeList = malloc(treeSize * sizeof(node));
  for (int i = 0; i < treeSize; i++)
    nodeList[i] = (node){malloc(4 * sizeof(int)), 0, 4};
  for (int i = 0; i < edgesSize; i++) {
    addNextNode(&nodeList[edges[i][0]], edges[i][1]);
    addNextNode(&nodeList[edges[i][1]], edges[i][0]);
  }
  return nodeList;
}

void freeTree(node *tree, int treeSize) {
  for (int i = 0; i < treeSize; i++)
    free(tree[i].nexts);
  free(tree);
}

void dfs(node *tree, int last, int curr, bool currIsEven, int *evenCnt,
         bool *isEven) {
  if (currIsEven)
    (*evenCnt)++;
  isEven[curr] = currIsEven;
  for (int i = 0; i < tree[curr].len; i++)
    if (tree[curr].nexts[i] != last)
      dfs(tree, curr, tree[curr].nexts[i], !currIsEven, evenCnt, isEven);
}

#define MAX(a, b) a > b ? a : b

int* maxTargetNodes(int** edges1, int edges1Size, int* edges1ColSize, int** edges2, int edges2Size, int* edges2ColSize, int* returnSize) {
    node *tree1 = restoreTree(edges1, edges1Size),
       *tree2 = restoreTree(edges2, edges2Size);

  int tree1Size = edges1Size + 1, tree2Size = edges2Size + 1;
  int evenCnt1 = 0, evenCnt2 = 0;
  bool isEven1[tree1Size], isEven2[tree2Size];
  dfs(tree1, -1, 0, true, &evenCnt1, isEven1);
  dfs(tree2, -1, 0, true, &evenCnt2, isEven2);

  int max = MAX(evenCnt2, tree2Size - evenCnt2);
  int evenRs = evenCnt1 + max, oddRs = tree1Size - evenCnt1 + max;
  int *rs = malloc(tree1Size * sizeof(int));
  for (int i = 0; i < tree1Size; i++)
    if (isEven1[i])
      rs[i] = evenRs;
    else
      rs[i] = oddRs;

  freeTree(tree1, tree1Size);
  freeTree(tree2, tree2Size);
  *returnSize = tree1Size;
  return rs;
}