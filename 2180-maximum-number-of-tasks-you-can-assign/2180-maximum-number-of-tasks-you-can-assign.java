class Solution {
    public int maxTaskAssign (int [] tasks, int [] workers, int pills, int strength) {
      int left = 0, right = Math.min (tasks.length, workers.length);
        Arrays.sort (tasks);
        Arrays.sort (workers);
        while (left < right) {
            int mid = (left + right + 1) / 2;
            int usedPills = 0;
            TreeMap <Integer, Integer> avail = new TreeMap <> ();
            for (int i = workers.length - mid; i < workers.length; ++i)
                avail.put (workers [i], avail.getOrDefault (workers [i], 0) + 1);
            boolean canAssign = true;
            for (int i = mid - 1; i >= 0; --i) {
                int w = avail.lastKey ();
                if (w >= tasks [i]) {
                    decrement (avail, w);
                } else {
                    Integer key = avail.ceilingKey (tasks [i] - strength);
                    if (key == null || ++usedPills > pills) {
                        canAssign = false;
                        break;
                    }
                    decrement (avail, key);
                }
            }
            if (canAssign)
                left = mid;
            else
                right = mid - 1;
        }

        return left;
    }
    private void decrement (TreeMap <Integer, Integer> mpp, int k) {
        int c = mpp.get (k);
        if (c == 1) mpp.remove (k);
        else mpp.put (k, c - 1);
    }
}