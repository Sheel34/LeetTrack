int gcd (int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

bool isGoodArray (int* nums, int numsSize) {
    int result = nums [0];
    for (int i = 0; i < numsSize; i++)
        result = gcd (result, nums [i]);
    if (result == 1)
        return true;
    return false;
}