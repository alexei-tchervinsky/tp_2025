#ifndef IOFMTGUARD_HPP
#define IOFMTGUARD_HPP

#include <ios>

namespace evdokimov {
class iofmtguard {
public:
  iofmtguard(std::basic_ios<char> &s);
  ~iofmtguard();

private:
  std::basic_ios<char> &s_;
  std::streamsize width_;
  char fill_;
  std::streamsize precision_;
  std::ios_base::fmtflags fmt_;
};
} // namespace evdokimov

#endif
