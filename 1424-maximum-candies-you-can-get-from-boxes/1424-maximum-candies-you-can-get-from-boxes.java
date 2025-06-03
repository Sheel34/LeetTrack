class Solution {
    public int maxCandies(int[] boxStatus, int[] boxCandies, int[][] boxKeys, int[][] boxContents, int[] startBoxes) {
        Queue<Integer> queue = new LinkedList<>();
        for (int b : startBoxes)
            queue.add(b);
        int total = 0;
        while (!queue.isEmpty()) {
            int box = queue.remove();
            if (boxStatus[box] == 0) {
                if (queue.isEmpty())
                    return total;
                queue.add(box);
            } else {
                total += boxCandies[box];
                for (int key : boxKeys[box])
                    boxStatus[key] = 1;
                for (int contained : boxContents[box])
                    queue.add(contained);
            }
        }
        return total;
    }
}