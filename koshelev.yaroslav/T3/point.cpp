#include "point.h"
#include "iofmtguard.h"
#include <sstream>

std::istream& operator>>(std::istream& in, Point& p) {
    koshelev::iofmtguard guard(in);
    char c1, c2, c3;
    if (in >> c1 >> p.x >> c2 >> p.y >> c3 &&
        c1 == '(' && c2 == ';' && c3 == ')') {
        return in;
        }
    in.setstate(std::ios::failbit);
    return in;
}

std::ostream& operator<<(std::ostream& out, const Point& p) {
    koshelev::iofmtguard guard(out);
    return out << '(' << p.x << ';' << p.y << ')';
}