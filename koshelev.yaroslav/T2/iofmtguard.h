#ifndef IOFMTGUARD_H
#define IOFMTGUARD_H

#include <ios>

namespace solution {

    class iofmtguard {
    public:
        explicit iofmtguard(std::basic_ios<char>& stream);
        ~iofmtguard();
    private:
        std::basic_ios<char>& stream_;
        char fill_;
        std::streamsize precision_;
        std::basic_ios<char>::fmtflags flags_;
    };

}

#endif
