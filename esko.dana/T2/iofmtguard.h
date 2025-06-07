
#ifndef IO_FMT_GUARD_HPP
#define IO_FMT_GUARD_HPP

#include <iostream>

namespace Data {
    class iofmtguard
    {
    public:
        iofmtguard(std::basic_ios<char>&);
        ~iofmtguard();

    private:
        std::basic_ios<char>& _s;
        std::streamsize _width;
        char _fill;
        std::streamsize _precision;
        std::basic_ios<char>::fmtflags _fmt;
    };
}

#endif
