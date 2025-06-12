#ifndef IOFMTGUARD_HPP
#define IOFMTGUARD_HPP

#include <iostream>

namespace solution {
    class iofmtguard {
    public:
        explicit iofmtguard(std::basic_ios<char>& stream);
        ~iofmtguard();

    private:
        std::basic_ios<char>& stream_;
        char fill_;
        std::streamsize precision_;
        std::ios::fmtflags flags_;
    };
}

#endif
