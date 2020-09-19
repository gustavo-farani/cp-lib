struct Node {
    void *lc, *rc;
};

// x: pointer to an already instantiated object
void* update (void* v, int l, int r, int i, void* x) {
    if (l == r) {
        return x;
    } else {
        int m = l + r >> 1;
        Node* p = new Node();
        if (v != nullptr) {
            *p = *(Node*)v;
        }
        if (i <= m) {
            p->lc = update(p->lc, l, m, i, x);
        } else {
            p->rc = update(p->rc, m + 1, r, i, x);
        }
        return p;
    }
}

// return: void pointer to the object in memory corresponding to i-th position
void* query (void* v, int l, int r, int i) {
    if (l == r) {
        return v;
    } else {
        int m = l + r >> 1;
        Node *p = (Node*)v;
        if (i <= m) {
            return query(p->lc, l, m, i);
        } else {
            return query(p->rc, m + 1, r, i);
        }
    }
}