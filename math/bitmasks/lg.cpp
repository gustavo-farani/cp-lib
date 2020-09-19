// n: positive integer (n != 0)
// return: the same as floor(log2(n))
int floorLg (int n) {
    return 32 - __builtin_clz(n) - 1;
}

// n: positive integer (n != 0)
// return: the same as ceil(log2(n))
int ceilLg (int n) {
    return n == 1 ? 0 : 1 + floorLg(n - 1);
}