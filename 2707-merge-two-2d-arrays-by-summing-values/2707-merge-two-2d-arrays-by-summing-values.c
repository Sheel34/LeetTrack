/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** mergeArrays(int** nums1, int nums1Size, int* nums1ColSize, int** nums2, int nums2Size, int* nums2ColSize, int* returnSize, int** returnColumnSizes) {
    *returnColumnSizes = (int*) malloc ((nums1Size + nums2Size) * sizeof (int)); 
    int** arr = (int**) malloc ((nums1Size + nums2Size) * sizeof (int*));
    int i = 0, j = 0, k = 0;
    while (i < nums1Size && j < nums2Size) {
        arr [k] = (int*) malloc (2 * sizeof (int));
        if (nums1 [i] [0] == nums2 [j] [0]) {
            arr [k] [0] = nums1 [i] [0];
            arr [k] [1] = nums1 [i] [1] + nums2 [j] [1];
            i++;
            j++;
        }
        else if (nums1 [i] [0] < nums2 [j] [0]) {
            arr [k] [0] = nums1 [i] [0];
            arr [k] [1] = nums1 [i] [1];
            i++;
        }
        else {
            arr [k] [0] = nums2 [j] [0];
            arr [k] [1] = nums2 [j] [1];
            j++;
        }
        (*returnColumnSizes) [k] = 2;
        k++;
    }
    while (i < nums1Size) {
        arr [k] = (int*) malloc (2 * sizeof (int));
        arr [k] [0] = nums1 [i] [0];
        arr [k] [1] = nums1 [i] [1];
        (*returnColumnSizes) [k] = 2;
        i++, k++;
    }
    while (j < nums2Size) {
        arr [k] = (int*) malloc (2 * sizeof (int));
        arr [k] [0] = nums2 [j] [0];
        arr [k] [1] = nums2 [j] [1];
        (*returnColumnSizes) [k] = 2;
        j++, k++;
    }
    *returnSize = k;
    return arr;
}