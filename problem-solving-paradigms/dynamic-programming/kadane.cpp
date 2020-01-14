typedef long long ll;

template <typename T>
ll kadane (T first, T last) {
    ll global, local;
    global = local = *first;
    for (auto it = next(first); it != last; it++) {
        local = max(*it, *it + local);
        global = max(global, local);
    }
    return global;
}