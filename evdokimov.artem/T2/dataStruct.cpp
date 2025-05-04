#include "dataStruct.hpp"
#include <iomanip>
#include <regex>

std::istream &operator>>(std::istream &in, DataStruct &data) {
  std::string line;
  while (std::getline(in, line)) {
    std::smatch match;

    if (!std::regex_match(line, std::regex(R"(\(:.*:\))"))) {
      continue;
    }

    std::regex key1Regex(R"(:key1 (0x[0-9a-fA-F]+):)");
    std::regex key2Regex(R"(:key2 #c\(([-+]?\d+\.?\d*)\s+([-+]?\d+\.?\d*)\):)");
    std::regex key3Regex(R"delim(:key3 "((?:[^"\\]|\\.)*)":)delim");
    bool ok = true;

    if (std::regex_search(line, match, key1Regex)) {
      try {
        data.key1 = std::stoull(match[1].str(), nullptr, 16);
      } catch (...) {
        ok = false;
      }
    } else {
      ok = false;
    }

    if (std::regex_search(line, match, key2Regex)) {
      try {
        double real = std::stod(match[1].str());
        double imag = std::stod(match[2].str());
        data.key2 = std::complex<double>(real, imag);
      } catch (...) {
        ok = false;
      }
    } else {
      ok = false;
    }

    if (std::regex_search(line, match, key3Regex)) {
      data.key3 = match[1].str();
    } else {
      ok = false;
    }

    if (ok) {
      return in;
    }
  }

  in.setstate(std::ios::failbit);
  return in;
}

std::ostream &operator<<(std::ostream &out, const DataStruct &data) {
  out << "(:key1 0x" << std::hex << std::uppercase << data.key1 << ":key2 #c("
      << std::fixed << std::setprecision(1) << data.key2.real() << " "
      << data.key2.imag() << "):key3 \"" << data.key3 << "\":)";
  return out;
}

bool compareDataStruct(const DataStruct &a, const DataStruct &b) {
  if (a.key1 != b.key1)
    return a.key1 < b.key1;
  double modA = std::abs(a.key2), modB = std::abs(b.key2);
  if (modA != modB)
    return modA < modB;
  return a.key3.length() < b.key3.length();
}
