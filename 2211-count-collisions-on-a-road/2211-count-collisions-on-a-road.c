#pragma GCC optimize ("O3, unroll-loops")

int countCollisions (char* dir) {
    const int n = strlen (dir);
    if (n == 1) return 0;
    int l = 0, r = n - 1;
    while (dir [l] == 'L') l++;
    while (l < r && dir [r] == 'R') r--;
    if (l >= r) return 0;
    int col = 0;
    for(; l <= r; l++) col += dir [l] != 'S';
    return col;
}