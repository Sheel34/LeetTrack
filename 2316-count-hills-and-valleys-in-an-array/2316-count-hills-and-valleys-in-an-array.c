int countHillValley (int* nums, int numsSize) {
    int count = 0;
    bool diff [2] = {0, 0};
    for (int i = 1; i < numsSize; i++){
        if (nums [i - 1] == nums [i]) continue;
        bool bigger = nums [i] > nums [i - 1];
        diff [bigger] = 1;
        count += diff [bigger] && diff [!bigger];
        diff [!bigger] = 0;
    }
    return count;
}