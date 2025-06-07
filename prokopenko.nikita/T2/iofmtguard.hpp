#pragma once
#include <iostream>

namespace prokopenko {

class iofmtguard {
    std::ios& s;
    char fill;
    std::streamsize precision;
    std::ios::fmtflags flags;

public:
    iofmtguard(std::ios& stream)
        : s(stream),
          fill(stream.fill()),
          precision(stream.precision()),
          flags(stream.flags()) {}

    ~iofmtguard() {
        s.fill(fill);
        s.precision(precision);
        s.flags(flags);
    }
};

} // namespace prokopenko
