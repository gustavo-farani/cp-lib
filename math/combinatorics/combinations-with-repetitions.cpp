#include "binomial-coefficient.cpp"
#include "../util/mod-base.cpp"

ModBase starsAndBars (int n, int k) {
    return combinations(n + k - 1, k);
}