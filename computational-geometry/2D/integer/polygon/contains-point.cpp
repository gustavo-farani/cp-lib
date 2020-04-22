struct ConvexPolygon {
    int sides;
    vector<PT> p;
    ConvexPolygon (vector<PT>&& v) : sides(v.size()), p(v) {
        // next line is unecessary if v was outputed from Grahan Scan
        rotate(p.begin(), min_element(p.begin(), p.end()), p.end());
        p.pb(p.front()); // facilitates iteration through edges
    }
    bool contains (const PT& q) {
        PT u = q - p[0];
        if (ccw(u, p[1] - p[0]) || ccw(p[sides - 1] - p[0], u)) {
            return false;
        } else {
            int l = 1, r = sides - 1;
            while (r - l > 1) {
                int m = l + r >> 1;
                if (!ccw(u, p[m] - p[0])) l = m;
                else r = m;
            }
            return !ccw(q - p[l], p[l + 1] - p[l]);
        }
    }
};