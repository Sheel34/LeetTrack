bool threeConsecutiveOdds(int* arr, int arrSize) {
    int n = arrSize, i = 0;
        while (i + 2 < n) {
            if ((arr [i] & 1) == 1 && (arr [i + 1] & 1) == 1 && (arr [i + 2] & 1) == 1)
                return true;
            if ((arr [i + 2] & 1) == 0) i += 3;
            else if ((arr [i + 1] & 1) == 0) i += 2;
            else i += 1;
        }
        return false;
}