#include "iofmtguard.hpp"
#include <ios>

geom_lab::iofmtguard::iofmtguard(std::basic_ios<char>& s) :
    s_(s), precision_(s.precision()), flags_(s.flags()) {}

geom_lab::iofmtguard::~iofmtguard()
{
    s_.precision(precision_);
    s_.flags(flags_);
}
