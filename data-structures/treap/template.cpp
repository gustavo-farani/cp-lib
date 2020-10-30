#include "../../random.cpp"

uniform_int_distribution<int> prio;

template<class T>
struct Rope {
    using Key = int;

    struct Node {
        int y;        // priority
        Node *l, *r;  // left and right children
        T val;        // mapped value
        
        // key value
        // ERASE if key is implicit
        Key x;

        // parent of node
        // ERASE if not a disjoint sets problem
        Node *f;

        // TODO declare subtree data
        int size;
    
        // TODO declare lazy flags
        // ERASE if not a lazy propagation problem
        bool reverse;
        pair<bool, T> fill;
        
        // implicit key version
        Node (const T& val) :
            y(prio(rng)), l(nullptr), r(nullptr), val(val),

            // TODO lazy flags initially disabled
            // ERASE if not a lazy propagation problem
            reverse(false), fill({false, T()})
        { fix(); }

        // ERASE if key is implicit
        Node (const Key& k, const T& val) : Node(val) { x = k; }


        // recompute the data concerning the subtree rooted at this node
        void fix () {
            f = nullptr;  // ERASE if not a disjoint sets problem

            // TODO piece of this node
            size = 1;

            if (l) {
                // before acessing data of left subtree, invoke push on it
                // ERASE if not a lazy propagation problem
                l->push();

                l->f = this;  // ERASE if not a disjoint sets problem
                
                // TODO piece of the left subtree
                size += l->size;
            }
            if (r) {
                // before acessing data of right subtree, invoke push on it
                // ERASE if not a lazy propagation problem
                r->push();

                r->f = this;  // ERASE if not a disjoint sets problem

                // TODO piece of the right subtree
                size += r->size;
            }
        }

        // TODO tackle lazy updates on this node and propagate to children
        // ERASE if not a lazy propagation problem
        void push () {  
            if (reverse) {
                swap(l, r);
                if (l) l->reverse ^= 1;
                if (r) r->reverse ^= 1;
                reverse = false;
            }
            if (fill.fi) {
                val = fill.se;
                if (l) {
                    l->fill = {true, val};
                    // TODO cancel any other lazy flag of left child (except for reverse)
                }
                if (r) {
                    r->fill = {true, val};
                    // TODO cancel any other lazy flag of right child (except for reverse)
                }
                fill.fi = false;
            }
            // here goes range increment, range xor, etc
            // note that these updates must be tackled ONLY AFTER the fill update
            /* template code:
            if () {    // check lazy flag
                // update the data of this node
                // not only attribute .val
                // but any other data concerning the overall subtree
                // must be updated too
                if (l) {
                    // update lazy flags of the left child,
                    // but don't change anything else
                }
                if (r) {
                    // update lazy flags of the right child,
                    // but don't change anything else
                }
                // set lazy flag to false
            } */
        }

        // find root of tree
        // ERASE if not a disjoint sets problem
        Node* find () {
            Node* cur = this;
            while (cur->f) cur = cur->f;
            return cur;
        }
    };

    // (implicit key version)
    // splits treap rooted at v in two treaps, rooted at sl and sr
    // sl := contains exactly sx nodes (the leftmost ones)
    // sr := contains the other nodes (the rightmost ones)
    void split (Node* v, int sx, Node*& sl, Node*& sr) {
        if (v) {
            v->push();       // ERASE if not a lazy propagation problem
            int x = v->l ? v->l->size : 0;
            if (sx <= x) {
                split(v->l, sx, sl, v->l);
                sr = v;
            } else {
                split(v->r, sx - x - 1, v->r, sr);
                sl = v;
            }
            v->fix();
        } else {
            sl = sr = nullptr;
        }
    }

    /* (explicit key version, disabled by default)
    // splits treap rooted at v in two treaps, rooted at sl and sr
    // sl := nodes with keys strictly less than sx
    // sr := nodes with keys grater than or equal to sx
    void split (Node* v, const Key& sx, Node*& sl, Node*& sr) {
        if (v) {
            v->push();       // ERASE if not a lazy propagation problem
            if (sx <= v->x) {
                split(v->l, sx, sl, v->l);
                sr = v;
            } else {
                split(v->r, sx, v->r, sr);
                sl = v;
            }
            v->fix();
        } else {
            sl = sr = nullptr;
        }
    }
    */
    
    // merge treaps ml and mr into a single treap, rooted at v
    void merge (Node*& v, Node* ml, Node* mr) {
        if (ml || mr) {
            if (!ml) {
                v = mr;
            } else if (!mr) {
                v = ml;
            } else {
                ml->push();  // ERASE if not a lazy propagation problem
                mr->push();  // ERASE if not a lazy propagation problem
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
    
    Node* root;
    Rope () : root(nullptr) {}
    
    // insert value x into the rope in such a way that
    // after insertion it lies in the i-th position (0-based)
    void insert (int i, const T& x) {
        Node *head, *tail;
        split(root, i, head, tail);
        merge(head, head, new Node(x));
        merge(root, head, tail);
    }
    
    // acess/modify the value at i-th position (0-based) of the rope
    T& operator[] (int i) {
        Node *head, *body, *tail;
        split(root, i, head, tail);
        split(tail, 1, body, tail);
        T& ans = body->val;
        merge(tail, body, tail);
        merge(root, head, tail);
        return ans;
    }

    // NOTE: the l, r limits of every operation are 0-based and both inclusive
    
    void reverse (int l, int r) {
        Node *head, *body, *tail;
        split(root, l, head, tail);
        split(tail, r - l + 1, body, tail);
        body->reverse ^= 1;
        merge(tail, body, tail);
        merge(root, head, tail);
    }

    // fill all values in the segment with x
    void fill (int l, int r, const T& x) {
        Node *head, *body, *tail;
        split(root, l, head, tail);
        split(tail, r - l + 1, body, tail);
        body->fill = {true, x};
        merge(tail, body, tail);
        merge(root, head, tail);
    }

    void erase (int l, int r) {
        Node *head, *body, *tail;
        split(root, l, head, tail);
        split(tail, r - l + 1, body, tail);
        merge(root, head, tail);
    }
    
    // make a cyclic shift to the right with the segment
    void shiftRight (int l, int r) {
        Node *head, *body, *tail, *pivot;
        split(root, l, head, tail);
        split(tail, r - l + 1, body, tail);
        split(body, r - l, body, pivot);
        merge(body, pivot, body);
        merge(tail, body, tail);
        merge(root, head, tail);
    }

    /* template code for range queries/updates:
    void range (int l, int r) {
        Node *head, *body, *tail;
        split(root, l, head, tail);
        split(tail, r - l + 1, body, tail);
        // use body
        merge(tail, body, tail);
        merge(root, head, tail);
    }
    */
};