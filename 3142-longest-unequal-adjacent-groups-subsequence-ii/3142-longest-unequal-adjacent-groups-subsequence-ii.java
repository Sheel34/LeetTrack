class Solution {
    public List<String> getWordsInLongestSubsequence(String[] words, int[] groups) {
        int n = words.length;
        long[] codes = new long[n];
        for (int i = 0; i < n; i++) {
            long code = 0;
            for (int j = 0; j < words[i].length(); j++) {
                code |= (long)(words[i].charAt(j) - 'a') << (5 * j);
            }
            codes[i] = code;
        }
        int[] dp = new int[n];
        int[] prev = new int[n];
        Arrays.fill(dp, 1);
        Arrays.fill(prev, -1);
        int maxLen = 1, maxIdx = 0;
        @SuppressWarnings("unchecked")
        HashMap<Long,List<Integer>>[][] patterns = new HashMap[11][];
        for (int i = 0; i < n; i++) {
            int L = words[i].length(), g = groups[i];
            if (patterns[L] == null) {
                patterns[L] = new HashMap[L];
                for (int j = 0; j < L; j++) patterns[L][j] = new HashMap<>();
            }
            long codeI = codes[i];
            int best = 1, bp = -1;
            for (int j = 0; j < L; j++) {
                long pat = codeI & ~(31L << (5 * j));
                List<Integer> lst = patterns[L][j].get(pat);
                if (lst != null) for (int k : lst) {
                    if (groups[k] != g && dp[k] + 1 > best) {
                        best = dp[k] + 1;
                        bp = k;
                    }
                }
            }
            dp[i] = best;
            prev[i] = bp;
            if (best > maxLen) {
                maxLen = best;
                maxIdx = i;
            }
            for (int j = 0; j < L; j++) {
                long pat = codeI & ~(31L << (5 * j));
                patterns[L][j].computeIfAbsent(pat, x -> new ArrayList<>()).add(i);
            }
        }
        List<String> res = new ArrayList<>();
        for (int cur = maxIdx; cur != -1; cur = prev[cur]) res.add(words[cur]);
        Collections.reverse(res);
        return res;
    }
}