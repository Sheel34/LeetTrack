class Solution {
    double myCache [] [] = new double [179] [179];
    private double soupServingsHelper (int a, int b) {
        if (a <= 0 && b <= 0) 
            return 0.5;
        else if (a <= 0) 
            return 1;
        else if (b <= 0) 
            return 0;
        else if (myCache [a] [b] != 0) 
            return myCache [a] [b]; 
        else {
            double output1 = soupServingsHelper (a - 4, b);
            double output2 = soupServingsHelper (a - 3, b - 1);
            double output3 = soupServingsHelper (a - 2, b - 2);
            double output4 = soupServingsHelper (a - 1, b - 3);
            if (a >= 4)
            myCache [a - 4] [b] = output1;
            if (a >= 3 && b >= 1) 
            myCache [a - 3] [b - 1] = output2;
            if (a >= 2 && b >= 2) 
            myCache [a - 2] [b - 2] = output3;
            if (a >= 1 && b >= 3)
            myCache [a - 1] [b - 3] = output4;
            return 0.25 * (output1 + output2 + output3 + output4);
        }
    }   
    public double soupServings (int n) {
        if (n >= 4451)
            return 1;
        n = (n + 24) / 25;
        return soupServingsHelper (n, n);
    }
}