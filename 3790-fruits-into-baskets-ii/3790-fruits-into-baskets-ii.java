class Solution {
    public int numOfUnplacedFruits (int [] fruits, int [] baskets) {
        int unplaced = 0;
        for (int i = 0; i < fruits.length; i++) {
            boolean placed = false;
            for (int j = 0; j < baskets.length; j++) {
                if (fruits [i] <= baskets [j]) {
                    baskets [j] = 0; 
                    placed = true;
                    break; 
                }
            }
            if (!placed)
                unplaced++;
        }
        return unplaced;
    }
}