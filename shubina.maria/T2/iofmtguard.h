#pragma once

#include <ios>
#include <iostream>

class iofmtguard {
public:
    explicit iofmtguard(std::basic_ios<char>& ios);
    ~iofmtguard();

private:
    std::basic_ios<char>& m_ios;
    std::streamsize m_precision;
    std::streamsize m_width;
    std::basic_ios<char>::fmtflags m_flags;
};

