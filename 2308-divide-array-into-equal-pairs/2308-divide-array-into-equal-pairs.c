bool divideArray (int* nums, int numsSize) {
    int arr[501] = {};
    for (int i = 0; i < numsSize; ++i) //{
        if (arr [nums [i]])
            arr [nums [i]]--;
        else
            arr [nums [i]]++;
    //}
    for (int i = 0; i < 501; i++)
        if (arr [i])
            return false;
    return true;
}