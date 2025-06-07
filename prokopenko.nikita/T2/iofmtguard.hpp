#ifndef IOFMTGUARD_HPP
#define IOFMTGUARD_HPP

#include <iostream>

namespace prokopenko {

<<<<<<< HEAD
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
=======
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
>>>>>>> 5562f3d43e256a43aea295b2fa950bc06f920b4c

}

#endif
