#include "boilerplate.cpp" 

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
    
/* An Interval Tree is a dynamic set that allows online
* insertion and removal of line intervals.
* Given a queried interval [ql, qr],
* if there is any interval [l, r] in the set such that l <= qr and ql <= r,
* then this intersecting interval can be found in logarithmic time
* (or it can be determined that there is no such interval)
* T: integral type for intervals endpoints
* (careless instantiation with floating-point types
* might result in precision errors)
*/
template<class T>
struct IntervalTree {
    // user defined node updator class for policy based tree
    template<class CNI, class NI, class _, class __>
    struct Update {
        typedef T metadata_type;
        virtual CNI node_begin() const = 0;
        virtual CNI node_end() const = 0;
        void operator() (NI v, CNI nil) {
            T x = (*v)->se;
            auto lc = v.get_l_child();
            if (lc != nil) x = max(x, lc.get_metadata());
            auto rc = v.get_r_child();
            if (rc != nil) x = max(x, rc.get_metadata());
            const_cast<T&>(v.get_metadata()) = x;
        }
        /* Finds any interval intersecting with [ql, qr],
        * returning a Const_Node_Iterator pointing to it,
        * or node_end(), if there are no intersections
        * Complexity: logarithmic on the tree size
        */
        CNI search (T ql, T qr) {
            CNI v = node_begin(), nil = node_end();
            while (v != nil) {
                T l = (*v)->fi.fi, r = (*v)->se;
                if (qr < l || r < ql) {
                    auto lc = v.get_l_child();
                    if (lc != nil && lc.get_metadata() >= ql) {
                        v = lc;
                    } else {
                        v = v.get_r_child();
                    }
                } else {
                    break;
                }
            }
            return v;
        }
    };
 
    tree<pair<T, int>, T, less<pair<T, int>>, rb_tree_tag, Update> t;
 
    /* Intervals are distinguished by their integer index i,
    * so that there can be multiple intervals sharing the same endpoints */
    void insert (T l, T r, int i) { t.insert({{l, i}, r}); }
    void erase (T l, T r, int i) { t.erase({l, i}); }
 
    bool hasOverlaps (T ql, T qr) {
        return t.search(ql, qr) != t.node_end();
    }
    tuple<T, T, int> findAnyOverlap (T ql, T qr) {
        auto v = t.search(ql, qr);
        if (v == t.node_end()) {
            throw -1;
        } else {
            T l, r;
            int i;
            tie(l, i) = (*v)->fi;
            r = (*v)->se;
            return {l, r, i};
        }
    }
};