#pragma GCC optimize ("O3", "unroll-loops")

int minCost (char* colors, int* neededTime, int n) {
    int l = 0;
    int removes = 0, locMax = 0;
    for (register int r = 0; r < n;) {
        while (r < n && colors [r] == colors [l]) {
            removes += neededTime [r];
            if (locMax < neededTime [r]) locMax = neededTime [r];
            r++;
        }
        removes -= locMax;
        locMax = 0;
        l = r; 
    }
    return removes;
}