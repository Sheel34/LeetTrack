/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

static inline int min (int a, int b) { return a < b ? a : b; }


int** highestPeak (int** isWater, int isWaterSize, int* isWaterColSize, int* returnSize, int** returnColumnSizes) {
    *returnSize = isWaterSize;
  *returnColumnSizes = isWaterColSize;

  int m = isWaterSize;
  int n = isWaterColSize [0];

  int** ret = isWater;

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      ret [i] [j] = !ret [i] [j] * 9999;
    }
  }

  for (int i = 0; i < m; i++) {
    for (int j = 1; j < n; j++) {
      ret [i] [j] = min (ret [i] [j], ret [i] [j - 1] + 1);
    }
  }

  for (int j = 0; j < n; j++) {
    for (int i = 1; i < m; i++) {
      ret [i] [j] = min (ret [i] [j], ret [i - 1] [j] + 1);
    }
  }

  for (int i = 0; i < m; i++) {
    for (int j = n - 2; j >= 0; j--) {
      ret [i][j] = min (ret [i] [j], ret [i] [j + 1] + 1);
    }
  }

  for (int j = 0; j < n; j++) {
    for (int i = m - 2; i >= 0; i--) {
      ret [i] [j] = min (ret [i] [j], ret [i + 1] [j] + 1);
    }
  }

  return ret;
}