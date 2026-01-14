class Solution {
    public double separateSquares (int [] [] squares) {
         List <double []> events = new ArrayList <> (); 

        for (int [] sq : squares) {
            int yi = sq [1], li = sq [2];

            events.add (new double [] {yi, li});
            events.add (new double [] {yi + li, -li});
        }

        events.sort ((a, b) -> Double.compare (a [0], b [0]));

        double total_w = 0.0;
        for (int [] sq : squares) {
            int li = sq [2];
            total_w += (double) li * li;
        }

        double target = total_w / 2.0;

        double curr_y = events.get (0) [0], curr_w = 0.0, accumulated = 0.0;

        for (int i = 0; i < events.size (); i++) {
            double [] event = events.get (i);
            double y = event [0], change = event [1];

            double separate = y - curr_y;
            accumulated += curr_w * separate;
        
            if (accumulated >= target) {
                double prev = accumulated - curr_w * separate;
                double need = target - prev;
                return curr_y + need / curr_w;
            }
            curr_y = y;
            curr_w += change;
        }
        return 0.0;
    }
}