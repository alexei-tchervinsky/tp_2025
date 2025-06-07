#ifndef IO_OBJECTS_HPP
#define IO_OBJECTS_HPP

#include <string>
#include <complex>
#include <iostream>

namespace prokopenko {

<<<<<<< HEAD
  struct DelimiterIO {
    char expected;
  };

  struct LabelIO {
    std::string& ref;
  };

  struct ComplexIO {
    std::complex<double>& ref;
  };

  struct CharIO {
    char& ref;
  };

  struct StringIO {
    std::string& ref;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&&);
  std::istream& operator>>(std::istream& in, LabelIO&&);
  std::istream& operator>>(std::istream& in, ComplexIO&&);
  std::istream& operator>>(std::istream& in, CharIO&&);
  std::istream& operator>>(std::istream& in, StringIO&&);

=======
    struct DelimiterIO {
        char expected;
    };

    struct LabelIO {
        std::string& ref;
    };

    struct CharIO {
        char& ref;
    };

    struct ULLIO {
        unsigned long long& ref;
    };

    struct StringIO {
        std::string& ref;
    };

    std::istream& operator>>(std::istream& in, DelimiterIO&&);
    std::istream& operator>>(std::istream& in, LabelIO&&);
    std::istream& operator>>(std::istream& in, CharIO&&);
    std::istream& operator>>(std::istream& in, ULLIO&&);
    std::istream& operator>>(std::istream& in, StringIO&&);
>>>>>>> 5562f3d43e256a43aea295b2fa950bc06f920b4c
}

#endif
