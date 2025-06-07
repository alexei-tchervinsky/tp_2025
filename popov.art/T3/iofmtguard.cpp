#include "iofmtguard.hpp"
popov::iofmtguard::iofmtguard(std::basic_ios<char>& s) :
    s_(s), precision_(s.precision()), flags_(s.flags()) {}
popov::iofmtguard::~iofmtguard()
{
    s_.precision(precision_);
    s_.flags(flags_);
}
