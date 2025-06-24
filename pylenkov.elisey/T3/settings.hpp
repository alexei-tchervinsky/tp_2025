#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <string>

// #define DO_LOG

#ifdef DO_LOG
#define LOG(s) \
{ \
  std::cout << s << '\n'; \
}
#else
#define LOG(S) {}
#endif // LOG

const std::string INV_CMD = "<INVALID COMMAND>\n" ;

#endif // SETTINGS_HPP
