#include "DataStruct.h"
#include <iomanip>
#include <sstream>
#include <algorithm>

namespace solution {

  std::istream& operator>>(std::istream& in, DataStruct& data) {
    std::string line;
    std::getline(in, line);

    if (line.empty()) {
      in.setstate(std::ios::failbit);
      return in;
    }

    std::istringstream iss(line);
    std::string temp;
    if (!(iss >> temp) || temp != "(:key1") {
      in.setstate(std::ios::failbit);
      return in;
    }

    if (!(iss >> temp) || temp.substr(0, 2) != "#c") {
      in.setstate(std::ios::failbit);
      return in;
    }

    temp.erase(0, 3);
    std::string real_str, imag_str;
    std::istringstream(temp) >> real_str;

    if (!(iss >> imag_str)) {
      in.setstate(std::ios::failbit);
      return in;
    }

    imag_str.pop_back();
    try {
      data.key1 = std::complex<double>(std::stod(real_str), std::stod(imag_str));
    } catch (...) {
      in.setstate(std::ios::failbit);
      return in;
    }

    if (!(iss >> temp) || temp != ":key2") {
      in.setstate(std::ios::failbit);
      return in;
    }

    if (!(iss >> temp) || temp != "(:N") {
      in.setstate(std::ios::failbit);
      return in;
    }

    long long numerator;
    unsigned long long denominator;
    if (!(iss >> numerator)) {
      in.setstate(std::ios::failbit);
      return in;
    }

    if (!(iss >> temp) || temp != ":D") {
      in.setstate(std::ios::failbit);
      return in;
    }

    if (!(iss >> std::hex >> denominator)) {
      in.setstate(std::ios::failbit);
      return in;
    }

    if (!(iss >> temp) || temp != ":)") {
      in.setstate(std::ios::failbit);
      return in;
    }

    data.key2 = {numerator, denominator};

    if (!(iss >> temp) || temp != ":key3") {
      in.setstate(std::ios::failbit);
      return in;
    }

    std::string str;
    if (!(iss >> std::quoted(str))) {
      in.setstate(std::ios::failbit);
      return in;
    }

    if (!(iss >> temp) || temp != ":)") {
      in.setstate(std::ios::failbit);
      return in;
    }

    data.key3 = str;
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const DataStruct& data) {
    out << "(:key1 #c(" << std::scientific << data.key1.real() << ' '
        << data.key1.imag() << ")"
        << ":key2 (:N " << std::dec << data.key2.first
        << ":D " << std::uppercase << std::hex << data.key2.second << ":)"
        << ":key3 " << std::quoted(data.key3) << ":)";
    return out;
  }

  bool operator<(const DataStruct& lhs, const DataStruct& rhs) {
    if (lhs.key1 != rhs.key1)
      return lhs.key1.real() < rhs.key1.real() ||
            (lhs.key1.real() == rhs.key1.real() && lhs.key1.imag() < rhs.key1.imag());
    if (lhs.key2 != rhs.key2)
      return lhs.key2 < rhs.key2;
    return lhs.key3.length() < rhs.key3.length();
  }

}
