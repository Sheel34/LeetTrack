int maxSum (int* nums, int numsSize) {
    int freq [201] = {0};    
    int result = 0, max_num = INT_MIN;
    for (int i = 0; i < numsSize; ++i){
        freq [nums [i] + 100]++;
        if (nums [i] > max_num) max_num = nums [i];
    }
    for (int i = 0; i < 201; ++i){
        int num = i - 100;
        if (freq [i] > 0 && num > 0)
            result += num;
    }
    if (result != max_num && result == 0)
        return max_num;
    return result;
}