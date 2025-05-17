#include "iofmtguard.hpp"

namespace narumov {
    iofmtguard::iofmtguard(std::basic_ios<char>& s):
        _s(s),
        _width(s.width()),
        _fill(s.fill()),
        _precision(s.precision()),
        _fmt(s.flags()) { }

    iofmtguard::~iofmtguard() {
        _s.width(_width);
        _s.fill(_fill);
        _s.precision(_precision);
        _s.flags(_fmt);
    }
}
