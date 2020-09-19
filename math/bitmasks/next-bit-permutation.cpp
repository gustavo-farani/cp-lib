// https://graphics.stanford.edu/~seander/bithacks.html
int nextBitPermutation (int v) {
    int t = v | v - 1;
    return t + 1 | (~t & -~t) - 1 >> __builtin_ctz(v) + 1;
}