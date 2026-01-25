class Solution {
    public int minimumPairRemoval (int [] nums) {
        int n = nums.length;
        long[] a = new long[n];
        for (int i = 0; i < n; i++) a[i] = nums[i];

        int[] l = new int[n], r = new int[n];
        boolean[] alive = new boolean[n];
        for (int i = 0; i < n; i++) {
            l[i] = i - 1;
            r[i] = i + 1;
            alive[i] = true;
        }
        r[n - 1] = -1;

        int bad = 0;
        for (int i = 1; i < n; i++)
            if (a[i] < a[i - 1]) bad++;

        PriorityQueue<long[]> pq = new PriorityQueue<>(
            (x, y) -> x[0] == y[0] ? Long.compare(x[1], y[1]) : Long.compare(x[0], y[0])
        );

        for (int i = 0; i + 1 < n; i++)
            pq.add(new long[]{a[i] + a[i + 1], i});

        int ops = 0;

        while (bad > 0) {
            long[] cur = pq.poll();
            long sum = cur[0];
            int i = (int) cur[1];

            if (!alive[i] || r[i] == -1) continue;
            int j = r[i];
            if (!alive[j] || a[i] + a[j] != sum) continue;

            int li = l[i], rj = r[j];

            if (li != -1 && a[i] < a[li]) bad--;
            if (rj != -1 && a[rj] < a[j]) bad--;
            if (a[j] < a[i]) bad--;

            a[i] += a[j];
            alive [j] = false;
            r [i] = rj;
            if (rj != -1) l [rj] = i;

            if (li != -1 && a [i] < a [li]) bad++;
            if (rj != -1 && a [rj] < a [i]) bad++;

            if (li != -1) pq.add (new long [] {a [li] + a [i], li});
            if (rj != -1) pq.add (new long [] {a [i] + a [rj], i});
            ops++;
        }
        return ops;
    }
}