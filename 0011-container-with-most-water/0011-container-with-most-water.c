int maxArea (int* height, int heightSize) {
    size_t r = 0;
    for (size_t i = 0, j = heightSize - 1; i != j; ) {
        r = fmax (r, fmin (height [i], height [j]) * (j - i));
        height [i] < height [j] ? ++i : --j;
    }
    return r;
}