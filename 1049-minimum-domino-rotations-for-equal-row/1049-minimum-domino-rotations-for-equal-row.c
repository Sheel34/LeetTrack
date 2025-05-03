int minDominoRotations (int* tops, int topsSize, int* bottoms, int bottomsSize) {
    int candidate1 = tops [0], candidate2 = bottoms [0];
    int countTops1 = 0, countBottoms1 = 0, same1 = 0;
    int countTops2 = 0, countBottoms2 = 0, same2 = 0;
    for (int i = 0; i < topsSize; i++) {
        if (tops [i] == candidate1) countTops1++;
        if (bottoms [i] == candidate1) countBottoms1++;
        if (tops [i] == candidate1 && bottoms [i] == candidate1) same1++;
        if (tops [i] == candidate2) countTops2++;
        if (bottoms [i] == candidate2) countBottoms2++;
        if (tops [i] == candidate2 && bottoms [i] == candidate2) same2++;
    }
    if (countTops1 + countBottoms1 - same1 == topsSize) {
        int rotations1 = topsSize - countTops1 < topsSize - countBottoms1 ? topsSize - countTops1 : topsSize - countBottoms1;
        return rotations1;
    }
    if (countTops2 + countBottoms2 - same2 == topsSize) {
        int rotations2 = topsSize - countTops2 < topsSize - countBottoms2 ? topsSize - countTops2 : topsSize - countBottoms2;
        return rotations2;
    }
    return -1;
}