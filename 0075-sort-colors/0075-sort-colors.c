#pragma GCC optimize("O3,unroll-loops")
#define swap(x, y){int (tmp)=(x); (x)=(y); (y)=(tmp);}

void sortColors(int* nums, int numsSize) {
    const char red = 0, white = 1, blue = 2;
    int l = 0, m = 0, r = numsSize - 1; // pointers to partition
    while (m <= r) {
        switch (nums[m]) {
        case red:
            swap(nums[l], nums[m]);
            l++, m++;
            break;
        case white:
            m++;
            break;
        case blue:
            swap(nums[m], nums[r]);
            r--;
        }
    }
}