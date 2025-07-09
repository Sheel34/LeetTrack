class Solution {
    public int maxFreeTime(int eventTime, int k, int[] startTime, int[] endTime) {
        int n = startTime.length; 
        List<Integer> gaps = new ArrayList<>(); 
        gaps.add(startTime[0]); 
        for (int i = 1; i < n; i++) { 
            gaps.add(startTime[i] - endTime[i - 1]); 
        } 
        gaps.add(eventTime - endTime[n - 1]); 
        int windowSum = 0; 
        for (int i = 0; i < k + 1; i++)
            windowSum += gaps.get(i); 
        int maxFree = windowSum; 
        for (int i = k + 1; i < gaps.size(); i++) {
            windowSum += gaps.get(i) - gaps.get(i - (k + 1)); 
            maxFree = Math.max(maxFree, windowSum); 
        } 
        return maxFree; 
    }
}