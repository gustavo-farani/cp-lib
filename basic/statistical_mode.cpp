#define pb push_back

template <typename T, class S>
vector<T> mode (S first, S last, int n) {  // [first, last) SORTED range
// T can assume an iterator for ANY sequential container:
// array, vector, deque, AND ALSO LIST
// only T should be passed as template argument (S is implicit)
// n must be passed as the pre-computed distance beetween first and last
    int maxFreq = 0;
    vector< vector<T> > table(n);
    S jt;
    for (S it = first; it != last; it = jt) {
        int len = -1;
        for (jt = it; jt != last && *it == *jt; jt++) {
            len++;
        }
        table[len].pb(*it);
        maxFreq = max(maxFreq, len);
    }
    return table[maxFreq]; // the returned vector should be passed 
    // as argument for a MOVE CONSTRUCTOR
}