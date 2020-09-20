#include "../../boilerplate.cpp"

template<class T>
struct MinQueue {
    list<T> q, u;
    void push (const T& x) {
        q.push_back(x);
        while (!u.empty() && u.back() > x) u.pop_back();
        u.push_back(x); 
    }
    void pop () {
        T& x = q.front();
        if (!u.empty() && u.front() == x) u.pop_front();
        q.pop_front();
    }
    T front () { return q.front(); }
    T min () { return u.empty() ? numeric_limits<T>::max() : u.front(); }
};