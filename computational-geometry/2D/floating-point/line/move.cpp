#include "line.cpp"

void Line::translate (PT u) { c += cross(v, u); }
void Line::reverse () { v.x = -v.x, v.y = -v.y, c = -c; }