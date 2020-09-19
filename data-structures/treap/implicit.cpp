#include "../../boilerplate.cpp"

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> uni;

template<class T>
struct List {
    struct Node {
        int y;
        Node *l, *r;
        int size;
        bool twist;
        T val;
        // TODO define satellite data members
        Node (const T& val) :
            y(uni(rng)), l(nullptr), r(nullptr),
            size(1), val(val), twist(false)
        {
            // TODO initialize satellite data for a single node
        }
    };

    // TODO define null-safe getter functions
    int sizeOf (Node* v) { return v == nullptr ? 0 : v->size; }
    void fix (Node* v) {
        if (v != nullptr) {
            v->size = 1 + sizeOf(v->l) + sizeOf(v->r);
            // TODO update attributes
        }
    }
    // TODO lazy propagation
    void push (Node* v) {
        if (v != nullptr && v->twist) {
            v->twist = false;
            swap(v->l, v->r);
            if (v->l != nullptr) v->l->twist ^= true;
            if (v->r != nullptr) v->r->twist ^= true;
        }
    }

    void split (Node* v, int sx, Node*& sl, Node*& sr) {
        if (v == nullptr) {
            sl = sr = nullptr;
        } else {
            push(v);
            int x = sizeOf(v->l);
            if (sx <= x) {
                split(v->l, sx, sl, v->l);
                sr = v;
            } else {
                split(v->r, sx - x - 1, v->r, sr);
                sl = v;
            }
            fix(v);
        }
    }
    void merge (Node*& v, Node* ml, Node* mr) {
        push(ml);
        push(mr);
        if (ml == nullptr) {
            v = mr;
        } else if (mr == nullptr) {
            v = ml;
        } else if (ml->y < mr->y) {
            merge(mr->l, ml, mr->l);
            v = mr;
        } else {
            merge(ml->r, ml->r, mr);
            v = ml;
        }
        fix(v);
    }
    Node* search (Node* v, int sx) {
        push(v);  // remeber to call push!
        int x = sizeOf(v->l);
        if (sx < x) {
            return search(v->l, sx);
        } else if (sx > x) {
            return search(v->r, sx - x - 1);
        } else {
            return v;
        }
    }

    Node* root;
    List () : root(nullptr) {}
    void insert (int i, const T& x) {
        Node *head, *tail;
        split(root, i, head, tail);
        merge(head, head, new Node(x));
        merge(root, head, tail);
    }
    T& operator[] (int i) {
        // assert(i >= 0 && i < sizeOf(root));
        return search(root, i)->val;
    }
    void reverse (int l, int r) {
        // assert(l <= r && l >= 0 && r < sizeOf(root));
        Node *head, *body, *tail;
        split(root, l, head, tail);
        split(tail, r - l + 1, body, tail);
        body->twist ^= true;
        merge(tail, body, tail);
        merge(root, head, tail);
    }
    void shiftRight (int l, int r) {
        Node *head, *body, *tail, *pivot;
        split(root, l, head, tail);
        split(tail, r - l + 1, body, tail);
        split(body, r - l, body, pivot);
        merge(body, pivot, body);
        merge(tail, body, tail);
        merge(root, head, tail);
    }
};