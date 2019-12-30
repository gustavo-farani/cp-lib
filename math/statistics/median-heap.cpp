#include <vector>
#include <queue>
using namespace std;

template <typename T>
struct MedianHeap {
    priority_queue<T> left; // Max Heap
    priority_queue< T, vector<T>, greater<T> > right; // Min Heap
    int size () { return left.size() + right.size(); }
    void push (T x) {
        if (!size()) {  // empty
            left.push(x);
        } else if (size() & 1) {   // odd
            if (x < left.top()) {
                right.push(left.top());
                left.pop();
                left.push(x);
            } else {
                right.push(x);
            }
        } else {  // even
            if (!(left.top() < x)) {
                left.push(x);
            } else {
                right.push(x);
                left.push(right.top());
                right.pop();
            }
        }
    }
    T median () {
        return left.top();
        // NOTE: when size() is even, the method can be easily
        // addapted to return make_pair(left.top(), right.top())
    }
};