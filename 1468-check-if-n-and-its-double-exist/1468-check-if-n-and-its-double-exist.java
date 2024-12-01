class Solution {
    public boolean checkIfExist (int [] arr) {
        
        int n = arr.length;
        
        for (int i = 0; i < n; i++){
            int target = arr [i] * 2;

            int val = searchFunc (arr, target, n);

            if (val != i && val != -1){
                return true;
            }
        }

        return false;
    }

    int searchFunc (int [] arr, int target, int n) {        
         for (int i = 0; i < n; i++) {            
            if (arr [i] == target) return i;
        }
        return -1;
    }
}