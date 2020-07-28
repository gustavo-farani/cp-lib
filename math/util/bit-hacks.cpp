// https://graphics.stanford.edu/~seander/bithacks.html

unsigned int nextBitPermutation (unsigned int v) {
    unsigned int t = v | (v - 1);
    return (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctz(v) + 1));
}

// n: positive integer (n != 0)
// return: the same as floor(log2(n))
unsigned int floorLg (unsigned int n) {
    return 32 - __builtin_clz(n) - 1;
}

// n: positive integer (n != 0)
// return: the same as ceil(log2(n))
unsigned int ceilLg (unsigned int n) {
    return n == 1 ? 0 : 1 + floorLg(n - 1);
}