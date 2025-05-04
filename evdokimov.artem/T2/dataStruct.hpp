#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <complex>
#include <iostream>
#include <string>

struct DataStruct {
  unsigned long long key1;
  std::complex<double> key2;
  std::string key3;
};

std::istream &operator>>(std::istream &in, DataStruct &data);
std::ostream &operator<<(std::ostream &out, const DataStruct &data);
bool compareDataStruct(const DataStruct &a, const DataStruct &b);

#endif
