#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <string>
#include <complex>
#include <iosfwd>

namespace prokopenko {

  struct DataStruct {
    std::complex<double> key1;
    char key2;
    std::string key3;

    bool operator<(const DataStruct& other) const;
  };

  std::istream& operator>>(std::istream& in, DataStruct& data);
  std::ostream& operator<<(std::ostream& out, const DataStruct& data);

}

#endif
