#include "iofmtguard.hpp"

namespace ilyaerofick {

IOFmtGuard::IOFmtGuard(std::basic_ios<char>& s) :
    s_(s), precision_(s.precision()), flags_(s.flags()) {}

IOFmtGuard::~IOFmtGuard() {
    s_.precision(precision_);
    s_.flags(flags_);
}

} // namespace ilyaerofick