#pragma once
#include <iostream>
#include "DataStruct.hpp"

namespace prokopenko {

struct CharIO {
    char& ref;
};

std::istream& operator>>(std::istream& in, CharIO&& c);
std::ostream& operator<<(std::ostream& out, const CharIO& c);

std::istream& operator>>(std::istream& in, DataStruct& ds);
std::ostream& operator<<(std::ostream& out, const DataStruct& ds);

} // namespace prokopenko
