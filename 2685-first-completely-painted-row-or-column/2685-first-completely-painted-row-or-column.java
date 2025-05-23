class Solution {
    public int firstCompleteIndex (int [] arr, int [] [] mat) {
        int rows = mat.length, cols = mat[0].length;
        Map<Integer, int[]> positionMap = new HashMap<>();
        
        int[] rowCount = new int[rows];
        int[] colCount = new int[cols];

        Arrays.fill (rowCount, cols);
        Arrays.fill (colCount, rows);

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                positionMap.put (mat [r] [c], new int [] {r, c});
            }
        }

        for (int index = 0; index < arr.length; ++index) {
            int [] pos = positionMap.get (arr [index]);
            if (--rowCount [pos [0]] == 0 || --colCount [pos [1]] == 0) {
                return index;
            }
        }
        return -1;
    }
}