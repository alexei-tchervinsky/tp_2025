#include "iofmtguard.h"

iofmtguard::iofmtguard(std::basic_ios<char>& ios)
    : m_ios(ios),
      m_precision(ios.precision()),
      m_width(ios.width()),
      m_flags(ios.flags())
{
}

iofmtguard::~iofmtguard()
{
    m_ios.precision(m_precision);
    m_ios.width(m_width);
    m_ios.flags(m_flags);
}

