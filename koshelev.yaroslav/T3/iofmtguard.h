#ifndef IOFMTGUARD_H
#define IOFMTGUARD_H

#include <ios>

namespace koshelev {

    class iofmtguard {
    public:
        explicit iofmtguard(std::ios& stream);
        ~iofmtguard();

    private:
        std::ios& stream_;
        char fillChar_;
        std::streamsize precision_;
        std::ios::fmtflags fmtFlags_;
    };

}

#endif // IOFMTGUARD_H

