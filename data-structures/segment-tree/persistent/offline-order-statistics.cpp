struct Node {
    int sum;
    Node *lc, *rc;
    Node (int x) : sum(x) {}
    Node (Node* lc, Node *rc) : lc(lc), rc(rc), sum(lc->sum + rc->sum) {}
    Node* update (int l, int r, int i) {
        if (l == r) {
            return new Node(sum + 1);
        } else {
            int m = l + r >> 1;
            if (i <= m) {
                return new Node(lc->update(l, m, i), rc);
            } else {
                return new Node(lc, rc->update(m + 1, r, i));
            }
        }
    }
};

Node* build (int l, int r) {
    if (l == r) {
        return new Node(0);
    } else {
        int m = l + r >> 1;
        return new Node(build(l, m), build(m + 1, r));
    }
}

template<class... Args>
int search (int l, int r, int k, Args*... p) {
    if (l == r) {
        return l;
    } else {
        int m = l + r >> 1;
        int cnt = (p->lc->sum - ...);
        if (k < cnt) {
            return search(l, m, k, p->lc...);
        } else {
            return search(m + 1, r, k - cnt, p->rc...);
        }
    }
}

// successfully tested with problems:
// https://www.spoj.com/problems/MKTHNUM/
// https://www.spoj.com/problems/COT/