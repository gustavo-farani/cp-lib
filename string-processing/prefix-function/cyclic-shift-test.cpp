#include "matching-as-ending-position.cpp"

template<class S>
bool isCyclicShift (const S& s, const S& t) {
    bool match = false;
    int n = s.size();
    if (n == t.size()) {
        S cat(t);
        cat.insert(cat.end(), t.begin(), t.end());
        vector<bool> end(patternMatching(s, cat));
        for (int i = n; i < cat.size() && !match; i++) {
            match |= end[i];
        }
    }
    return match;
}