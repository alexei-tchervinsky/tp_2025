#ifndef IOFMTGUARD_HPP
#define IOFMTGUARD_HPP

#include <iostream>

namespace orlov
{
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

#endif // !__IOFMTGUARD_HPP

