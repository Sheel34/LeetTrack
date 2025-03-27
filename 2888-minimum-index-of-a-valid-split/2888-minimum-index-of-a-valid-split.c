int minimumIndex (int* nums, int numsSize) {
    int max_i = 0;
    int max_r = 0;
    int max_l = 0;
    int right = numsSize;
    int left = 0;
    int count = 0;
    for (int i = 0; i < numsSize; i++) {
        if (count == 0) {
            max_i = nums [i];
            count = 1;
        } else if (max_i == nums [i])
            count++;
        else
            count--;
    }
    for (int i = 0; i < numsSize; i++)
        if (nums[i] == max_i) max_r++;
    for (int i = 0; i < numsSize; i++){
        right--; left++;
        if (nums [i] == max_i){
            max_r--; max_l++;
            if (max_r > right / 2 && max_l > left / 2) return i;
        }
    }
    return -1;
}