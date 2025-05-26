#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <complex>
#include <string>

namespace evdokimov {
enum key_type { HEX = 1, COMPLEX = 2, STRING = 3 };

struct DataStruct {
  unsigned long long key1_;
  std::complex<double> key2_;
  std::string key3_;
  friend std::ostream &operator<<(std::ostream &out, const DataStruct &src);
  friend std::istream &operator>>(std::istream &in, DataStruct &dest);

private:
  static void formatDouble(std::ostream &out, double num);
};

bool sortByCriteria(const DataStruct &a, const DataStruct &b);
} // namespace evdokimov

#endif
