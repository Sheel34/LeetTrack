/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

bool backtrack (int *arr ,int *visited, int size ,int  n, int index , int count) {
    if (count == n) return true;
    for (int i = n; i >= 1; i--) {
        int j = i == 1 ? index : index + i;
        if (visited [i] || j >= size || arr [index] || arr [j]) continue;
        arr [index] = arr [j] = i;
        visited [i] = 1;
        int next_index = index;
        while (next_index < size && arr [next_index]) next_index++;
        if (backtrack (arr , visited , size , n , next_index , count + 1)) return true;
        arr [index] = arr [j] = visited [i] = 0;
    }
    return false;
}

int* constructDistancedSequence (int n, int* returnSize) {
    int size = n * 2 - 1;
    int *arr = calloc (size , sizeof (int));
    int *vis = calloc (n + 1 , sizeof (int));
    backtrack (arr , vis , size , n , 0 , 0);
    *returnSize = size;
    return arr;
}