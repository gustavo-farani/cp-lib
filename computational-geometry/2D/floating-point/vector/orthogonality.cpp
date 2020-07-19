#include "point.cpp"

bool perp (PT u, PT v) { return sgn(dot(u, v)) == 0; }
PT perp (PT v) { return PT(-v.y, v.x); }  // CCW