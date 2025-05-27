#ifndef IOFMTGUARD_HPP
#define IOFMTGUARD_HPP

#include <iostream>

namespace ponomarenko {

    class iofmtguard {
    public:
        iofmtguard(std::basic_ios<char>& stream);
        ~iofmtguard();
    private:
        std::basic_ios<char>& stream_;
        char fill_;
        std::streamsize precision_;
        std::basic_ios<char>::fmtflags flags_;
    };

}

#endif
