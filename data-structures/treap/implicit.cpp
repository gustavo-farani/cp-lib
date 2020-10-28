#include "../../boilerplate.cpp"

uniform_int_distribution<int> prio;

template<class T>
struct Rope {
    struct Node {
        int y;
        Node *l, *r;
        T val;

        // TODO define subtree data
        int size;

        // TODO define lazy flags
        bool reverse;
        
        Node (const T& val) :
            y(prio(rng)), l(nullptr), r(nullptr), val(val),
            // TODO reset lazy flags
            reverse(false)
        { fix(); }

        void fix () {
            if (l && r) {
                size = l->size + 1 + r->size;
            } else if (l) {
                size = l->size + 1;
            } else if (r) {
                size = 1 + r->size;
            } else {
                size = 1;
            }
        }

        void push () {
            /* lazy propagation template
            if () {     // check lazy flag
                // fix val
                if (l) {
                    // set lazy flag of left child
                }
                if (r) {
                    // set lazy flag of right child
                }
                // reset lazy flag
            }
            */
           if (reverse) {     // check lazy flag
                // fix val
                swap(l, r);
                if (l) {
                    // set lazy flag of left child
                    l->reverse ^= 1;
                }
                if (r) {
                    // set lazy flag of right child
                    r->reverse ^= 1;
                }
                // reset lazy flag
                reverse = false;
            }
        }
    };

    void split (Node* v, int sx, Node*& sl, Node*& sr) {
        if (v) {
            push(v);
            int x = v->l ? v->l->size : 0;
            if (sx <= x) {
                split(v->l, sx, sl, v->l);
                sr = v;
            } else {
                split(v->r, sx - x - 1, v->r, sr);
                sl = v;
            }
            fix(v);
        } else {
            sl = sr = nullptr;
        }
    }

    void merge (Node*& v, Node* ml, Node* mr) {
        if (ml || mr) {
            if (!ml) {
                mr->push();
                v = mr;
            } else if (!mr) {
                ml->push();
                v = ml;
            } else {
                ml->push();
                mr->push();
                if (ml->y < mr->y) {
                    merge(mr->l, ml, mr->l);
                    v = mr;
                } else {
                    merge(ml->r, ml->r, mr);
                    v = ml;
                }
            }
            v->fix();
        } else {
            v = nullptr;
        }
    }

    Node* search (Node* v, int sx) {
        push(v);  // remeber to call push!
        int x = v->l ? vl->size : 0;
        if (sx < x) {
            return search(v->l, sx);
        } else if (sx > x) {
            return search(v->r, sx - x - 1);
        } else {
            return v;
        }
    }

    Node* root;
    Rope () : root(nullptr) {}

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

    void erase (int l, int r) {
        Node *head, *body, *tail;
        split(root, l, head, tail);
        split(tail, r - l + 1, body, tail);
        merge(root, head, tail);
    }

    void swap (int i, int j, int len) {
        Node* v[5];
        split(root, i, v[0], v[1]);
        split(v[1], len, v[1], v[2]);
        split(v[2], j - (i + len), v[2], v[3]);
        split(v[3], len, v[3], v[4]);
        merge(v[0], v[0], v[3]);
        merge(v[2], v[2], v[1]);
        merge(v[2], v[2], v[4]);
        merge(root, v[0], v[2]);
    }

    void reverse (int l, int r) {
        // assert(l <= r && l >= 0 && r < sizeOf(root));
        Node *head, *body, *tail;
        split(root, l, head, tail);
        split(tail, r - l + 1, body, tail);
        body->reverse ^= true;
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