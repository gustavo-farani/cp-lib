const int N = 18;

// adjacency matrix of weighted graph
// adj[u][v]: time to travel directly from u to v,
// with 0 <= u, v < N (0-indexing throughout the code)
// NOTE: adj[u][v] must be set to 0x3f3f3f3f, if there is
// no direct edge from u to v
int adj[N][N];

// finds a hamiltonian path with minimum length in a graph with n vertices
// the returned value is the measure of the minimum length,
// or 0x3f3f3f3f, if the given graph contains no hamiltonian paths
// the permutation of [0, n) representing the order
// in which vertices are visited (from first to last) is pushed to vector p
// NOTE: assumes the maximum possible length of a hamiltonian
// path is always less than 0x3f3f3f3f
int tsp (int n, vi& p) {
    int dp[1 << N][N];
    memset(dp, 0x3f, sizeof dp);
    int from[1 << N][N];
    memset(from, -1, sizeof from);
    // trivial case: just one vertex visited
    for (int i = 0, bi = 1; i < n; i++, bi <<= 1) {
        dp[bi][i] = 0;
    }
    const int all = (1 << n) - 1;
    for (int sub = 1; sub < all; sub++) {
        for (int i = 0, bi = 1; i < n; i++, bi <<= 1) {
            if (!(bi & sub)) continue;
            for (int j = 0, bj = 1; j < n; j++, bj <<= 1) {
                if (bj & sub) continue;
                int sup = sub|bj;
                // tries to relax dp[sup][j]
                if (dp[sub][i] + adj[i][j] < dp[sup][j]) {
                    dp[sup][j] = dp[sub][i] + adj[i][j];
                    from[sup][j] = i;
                }
            }
        }
    }
    // finds the measure of the optimal length, if possible
    int ans = 0x3f3f3f3f, j = -1;
    for (int i = 0; i < n; i++) {
        if (dp[all][i] < ans) {
            ans = dp[all][i];
            j = i;
        }
    }
    // iterates backwards along the optimal hamiltonian path, if any
    int super = all;
    while (j != -1) {
        p.pb(j);
        int sub = super ^ 1 << j, i = from[super][j];
        super = sub, j = i;
    }
    reverse(p.begin(), p.end());
    return ans;
}

// returns the minimum length of a hamiltonian path in a graph with n vertices,
// or 0x3f3f3f3f, if the given graph contains no hamiltonian paths
// NOTE: assumes the maximum possible length of a hamiltonian
// path is always less than 0x3f3f3f3f
int tsp (int n) {
    int dp[1 << N][N];
    memset(dp, 0x3f, sizeof dp);
    // trivial case: just one vertex visited
    for (int i = 0, bi = 1; i < n; i++, bi <<= 1) {
        dp[bi][i] = 0;
    }
    const int all = (1 << n) - 1;
    for (int sub = 1; sub < all; sub++) {
        for (int i = 0, bi = 1; i < n; i++, bi <<= 1) {
            if (!(bi & sub)) continue;
            for (int j = 0, bj = 1; j < n; j++, bj <<= 1) {
                if (bj & sub) continue;
                int sup = sub|bj;
                // tries to relax dp[sup][j]
                dp[sup][j] = min(dp[sup][j], dp[sub][i] + adj[i][j]);
            }
        }
    }
    // finds the measure of the optimal length, if possible
    return *min_element(dp[all], dp[all] + n);
}