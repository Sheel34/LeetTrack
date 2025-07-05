class Solution {
    public int findLucky (int [] arr) {
        int count = 0, max = Integer.MIN_VALUE;
        for (int i = 0; i < arr.length; i++) {
            count = 0;
            int num = arr [i];
            for (int j = 0; j < arr.length; j++) {
                if (num == arr [j])
                    count++;
            }
            if (num == count)
                max = Math.max (num, max);
        }
        if (max == Integer.MIN_VALUE)
            return -1;
        else
            return max;
    }
}