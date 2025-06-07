#include "iofmtguard.hpp"
#include <ios>
//сохраняем текущее состояние потока
erofick::iofmtguard::iofmtguard(std::basic_ios<char>& s) :
    s_(s), precision_(s.precision()), flags_(s.flags()) {}
//восстанавливаем соъраненное состояние потока
erofick::iofmtguard::~iofmtguard()
{
    s_.precision(precision_);
    s_.flags(flags_);
}
