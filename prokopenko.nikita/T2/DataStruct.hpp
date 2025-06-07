#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <complex>
#include <string>
#include <iostream>

namespace prokopenko {
<<<<<<< HEAD

  struct DataStruct {
    std::complex<double> key1;
    char key2;
    std::string key3;
    bool operator<(const DataStruct& other) const;
  };

  std::istream& operator>>(std::istream& in, DataStruct& data);
  std::ostream& operator<<(std::ostream& out, const DataStruct& data);

=======
    struct DataStruct {
        char key1;
        unsigned long long key2;
        std::string key3;
        bool operator<(const DataStruct& other) const;
    };

    std::istream& operator>>(std::istream& in, DataStruct& data);
    std::ostream& operator<<(std::ostream& out, const DataStruct& data);
>>>>>>> 5562f3d43e256a43aea295b2fa950bc06f920b4c
}

#endif
