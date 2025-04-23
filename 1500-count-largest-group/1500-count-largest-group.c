#define MAX_DIGIT_SUM 36

int digit_sums [MAX_DIGIT_SUM + 1];

int get_digit_sum (int n) {
    int sum = 0;
    while (n) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}
int countLargestGroup (int n) {
    memset (digit_sums, 0, (MAX_DIGIT_SUM + 1) * sizeof (int));
    for (int i = 1; i <= n; ++i) {
        int digit_sum = get_digit_sum (i);
        digit_sums [digit_sum]++;
    }
    int max_size = 0;
    int counter = 0;
    for (int i = 0; i <= MAX_DIGIT_SUM; ++i) {
        if (digit_sums [i] > max_size) {
            max_size = digit_sums [i];
            counter = 0;
        }
        counter += (digit_sums [i] == max_size);
    }
    return counter;
}