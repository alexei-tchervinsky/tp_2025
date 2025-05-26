#include "iofmtguard.hpp"
#include <ios>

marfina::iofmtguard::iofmtguard(std::basic_ios<char>& s) :
    s_(s), precision_(s.precision()), flags_(s.flags()) {}

marfina::iofmtguard::~iofmtguard()
{
    s_.precision(precision_);
    s_.flags(flags_);
}
