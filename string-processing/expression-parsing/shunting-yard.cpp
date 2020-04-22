#include "../../template.cpp"

template<class T>
struct Parser {
    // !TODO define how many arguments each operator takes
    // also, character token c will represent an operator iff args(c) > 0
    int args (char c) {
        switch (c) {
            case '*':
            case '+':
                return 2;
            case '-':
                return 1;
            default:
                return 0;  // if not an operator
        }
    }
    // !TODO define the precedence of the operators
    // unary operators must have higher precedence relative to the binary ones
    int rank (char c) {
        switch (c) {
            case '-':
                return 0;
            case '*':
                return -1;
            case '+':
                return -2;
        }
    }
    // !TODO define the association rule for the operators
    // true: binary left-associative operators (+ plus, - minus)
    // or unary left-associative operators (-> pointer arrow, . attribute dot)
    // false: binary right-associative operators (** Python exponentiation)
    // or unary right-associative operators (- unary negative, * pointer dereference)
    bool ltr (char c) {
        switch (c) {
            case '*':
            case '+':
                return true;
            case '-':
                return false;
        }
    }
    // !TODO match the token to the corresponding binary operation
    T eval (T x, T y, char c) {
        switch (c) {
            case '*':
                return x*y;
            case '+':
                return x + y;
        }
    }
    // !TODO match the token to the corresponding unary operation
    T eval (T x, char c) {
        switch (c) {
            case '-':
                return !x;
        }
    }
    // !TODO parse literal expression
    T lit (string& buf) {
        return stoi(buf);
    }
    void flsh (stack<T>& v, string& buf) {
        if (!buf.empty()) {
            v.push(lit(buf));
            buf.clear();
        }
    }
    void pop (stack<T>& v, char c) {
        T y = v.top();
        v.pop();
        if (args(c) == 2) {
            T x = v.top();
            v.pop();
            v.push(eval(x, y, c));
        } else {
            v.push(eval(y, c));
        }
    }
    T operator() (const string& s) {
        stack<T> v;
        stack<char> o;
        string buf;
        for (char c : s) {
            if (c == '(') {
                flsh(v, buf);
                o.push(c);
            } else if (c == ')') {
                flsh(v, buf);
                while (o.top() != '(') {
                    pop(v, o.top());
                    o.pop();
                }
                o.pop();
            } else if (args(c) > 0) {
                flsh(v, buf);
                while (!o.empty() && o.top() != '(' &&
                (rank(o.top()) > rank(c) || rank(o.top()) == rank(c) && ltr(c))) {
                    pop(v, o.top());
                    o.pop();
                }
                o.push(c);
            } else if (c != ' ') {  // ignore spaces
                buf.pb(c);
            }
        }
        flsh(v, buf);
        while (!o.empty()) {
            pop(v, o.top());
            o.pop();
        }
        return v.top();
    }
};