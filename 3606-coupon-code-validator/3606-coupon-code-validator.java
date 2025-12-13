class Solution {
    public List <String> validateCoupons (String [] code, String [] line, boolean [] active) {
        int n = code.length;
        Map <String, Integer> lineId = new HashMap <> ();
        lineId.put ("electronics", 1);
        lineId.put ("grocery", 2);
        lineId.put ("pharmacy", 3);
        lineId.put ("restaurant", 4);
        List <Integer> valid = new ArrayList <> ();
        for (int i = 0; i < n; i++) {
            if (!lineId.containsKey (line [i]) || code [i] == null || code [i].isEmpty ()) { 
                active [i] = false;
            }
            if (active [i]) {
                for (char c : code [i].toCharArray ()) {
                    if (!isGoodChar (c)) {
                        active [i] = false;
                        break;
                    }
                }
            }
            if (active [i])
                valid.add (i);
        }
        valid.sort ((i, j) -> {
            int li = lineId.get (line [i]);
            int lj = lineId.get (line [j]);
            if (li != lj) return Integer.compare (li, lj);
            return code [i].compareTo (code [j]);
        });
        List <String> ans = new ArrayList <> (valid.size ());
        for (int idx : valid)
            ans.add (code [idx]);
        return ans;
    }
    private boolean isGoodChar (char c) {
        return Character.isLetterOrDigit (c) || c == '_';
    }
}