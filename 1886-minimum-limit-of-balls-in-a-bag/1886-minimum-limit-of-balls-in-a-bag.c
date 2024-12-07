int canDivide (int* nums, int numsSize, int maxOperations, int penalty) {
    
    int operations = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums [i] > penalty) {
            operations += (nums [i] - 1) / penalty;
            if (operations > maxOperations) {
                return 0;
            }
        }
    }
    return 1;
}

int minimumSize (int* nums, int numsSize, int maxOperations) {

    int left = 1, right = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums [i] > right) {
            right = nums [i];
        }
    }

    int result = right;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (canDivide (nums, numsSize, maxOperations, mid)) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return result;
}