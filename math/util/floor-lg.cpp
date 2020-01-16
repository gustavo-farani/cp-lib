int floorlg (int n) {
    return (31 - __builtin_clz(n));
}