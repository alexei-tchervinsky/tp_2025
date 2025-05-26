#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <complex>
#include <string>

namespace evdokimov {
enum key_type { HEX = 1, COMPLEX = 2, STRING = 3 };

struct DataRecord {
  unsigned long long val1_;
  std::complex<double> val2_;
  std::string val3_;
  friend std::ostream &operator<<(std::ostream &out, const DataRecord &src);
  friend std::istream &operator>>(std::istream &in, DataRecord &dest);

private:
  static void formatDouble(std::ostream &out, double num);
};

bool sortByCriteria(const DataRecord &a, const DataRecord &b);
} // namespace evdokimov

#endif
