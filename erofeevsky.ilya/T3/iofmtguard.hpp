#ifndef IOFMTGUARD_HPP
#define IOFMTGUARD_HPP

#include <ios>

namespace ilyaerofick {

class IOFmtGuard {
public:
    explicit IOFmtGuard(std::basic_ios<char>& s);
    ~IOFmtGuard();
private:
    std::basic_ios<char>& s_;
    std::streamsize precision_;
    std::basic_ios<char>::fmtflags flags_;
};

}

#endif